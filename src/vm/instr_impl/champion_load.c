/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champion_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 16:57:29 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/18 18:08:14 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "unistd.h"
#include <sys/stat.h>
#include <fcntl.h>

/* TODO python interface for this */

int		vm_champion_load_file(t_vm_state *state, const char *filename)
{
	int	fd;
	int	ret;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-2);
	ret = vm_champion_load(state, fd);
	close(fd);
	return (ret);
}

int		vm_champion_load(t_vm_state *state, int fd)
{
	t_player	player;
	int			ret;

	ret = read_whole(fd, &player.header, sizeof(t_header));
	/* TODO good error handling */
	if (ret < sizeof(t_header))
		return (-1);
	if (player.header.prog_size > CHAMP_MAX_SIZE)
		return (-1);
	player.champion_code = malloc(player.header.prog_size);
	ret = read_whole(fd, &player.champion_code, player.header.prog_size);
	if (ret < player.header.prog_size)
		return (-1);
	/* TODO check if the file is over? */
	array_push_back(&state->players, &player);
	return (0);
}

void	vm_memory_prepare(t_vm_state *state)
{
	size_t	address;
	size_t	champion;

	ft_bzero(&state->memory, MEM_SIZE);
	champion = 0;
	while (champion < ft_min(state->players.length, MAX_PLAYERS))
	{
		address = (MEM_SIZE / state->players.length) * champion;
		ft_memcpy(&state->memory[address],
			ARRAY_PTR(state->players, t_player)[champion].champion_code,
			ARRAY_PTR(state->players, t_player)[champion].header.prog_size);
		champion++;
	}
}
