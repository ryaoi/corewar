/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:57:29 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/20 14:50:08 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

/* TODO python interface for this */

int		vm_champion_load_file(t_vm_state *state, const char *filename, int id)
{
	int	fd;
	int	ret;

	/* TODO check there's no other champion with the same id */
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "Error opening file %s: %s\n",
			filename, strerror(errno));
		return (ERR_FILE);
	}
	ret = vm_champion_load(state, fd, id);
	close(fd);
	if (ret == ERR_HEADER_READ)
		ft_dprintf(2,
			"Error reading file %s: unexpected eof before end of header\n",
			filename);
	else if (ret == ERR_CHAMP_TOO_LARGE)
		ft_dprintf(2,
			"Error reading file %s: program size too large\n",
			filename);
	else if (ret == ERR_CHAMP_READ)
		ft_dprintf(2,
			"Error reading file %s: unexpected eof before end of bytecode\n",
			filename);
	return (ret);
}

int		vm_champion_load(t_vm_state *state, int fd, int id)
{
	t_player	player;
	int			ret;

	ret = read_whole(fd, (char*)&player.header, sizeof(t_header));
	/* TODO good error handling */
	if (ret < (long)sizeof(t_header))
		return (ERR_HEADER_READ);
	/* TODO check magic number in header */
	player.header.prog_size = byte_order_swap(
		(t_bigend_buffer){(size_t)player.header.prog_size << 32}).buffer;
	if (player.header.prog_size > CHAMP_MAX_SIZE)
		return (ERR_CHAMP_TOO_LARGE);
	player.champion_code = malloc(player.header.prog_size);
	ret = read_whole(fd, (char*)player.champion_code, player.header.prog_size);
	if (ret < (int32_t)player.header.prog_size)
		return (ERR_CHAMP_READ);
	/* TODO check if the file is over? */
	player.live = 0;
	player.id = id;
	array_push_back(&state->players, &player);
	return (0);
}
