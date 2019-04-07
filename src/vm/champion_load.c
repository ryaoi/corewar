/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:57:29 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/06 18:50:17 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_assert.h"
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

static const char	*champload_strerror(int error)
{
	if (error == ERR_HEADER_READ)
		return ("unexpected eof before end of header");
	else if (error == ERR_CHAMP_TOO_LARGE)
		return ("program size too large");
	else if (error == ERR_CHAMP_READ)
		return ("unexpected eof before end of bytecode");
	else if (error == ERR_HEADER_MAGIC)
		return ("magic number not matching");
	else
		return ("error code invalid");
}

int					vm_champion_load_file(t_player *player,
						const char *filename, int id)
{
	int	fd;
	int	ret;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "Error opening file %s: %s\n",
			filename, strerror(errno));
		return (ERR_FILE);
	}
	ret = vm_champion_load(player, fd, id);
	close(fd);
	if (ret < 0)
		ft_dprintf(2, "Error reading file %s: %s\n", filename,
			champload_strerror(ret));
	return (ret);
}

int					vm_champion_load(t_player *player, int fd, int id)
{
	int			ret;

	ret = read_whole(fd, (char*)&player->header, sizeof(t_header));
	if (ret < (long)sizeof(t_header))
		return (ERR_HEADER_READ);
	player->header.magic = byte_order_swap(
		(t_bigend_buffer){player->header.magic}).buffer;
	if (player->header.magic != COREWAR_EXEC_MAGIC)
		return (ERR_HEADER_MAGIC);
	player->header.prog_size = byte_order_swap(
		(t_bigend_buffer){player->header.prog_size}).buffer;
	if (player->header.prog_size > CHAMP_MAX_SIZE)
		return (ERR_CHAMP_TOO_LARGE);
	player->champion_code = malloc(player->header.prog_size);
	MALLOC_ASSERT(player->champion_code);
	ret = read_whole(fd, (char*)player->champion_code,
		player->header.prog_size);
	if (ret < (int32_t)player->header.prog_size)
		return (ERR_CHAMP_READ);
	player->live = 0;
	player->id = id;
	return (0);
}
