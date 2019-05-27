/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_memory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 19:27:10 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 18:41:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static void	color_memory(t_vm_state *state, int id,
				size_t address, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		state->memory_info[address + index].written_player = id;
		index++;
	}
}

void		vm_memory_prepare(t_vm_state *state)
{
	size_t	address;
	size_t	champion;

	ft_bzero(&state->memory, MEM_SIZE);
	state->process_count = 1;
	champion = 0;
	while (champion < (size_t)ft_min(state->players.length, MAX_PLAYERS))
	{
		address = (MEM_SIZE / state->players.length) * champion;
		ft_memcpy(&state->memory[address],
			(player_get(state, champion))->champion_code,
			(player_get(state, champion))->header.prog_size);
		color_memory(state,
			(player_get(state, champion))->id, address,
			(player_get(state, champion))->header.prog_size);
		champion++;
	}
}
