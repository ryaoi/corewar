/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/05/20 17:27:26 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static void	clear_pc_info(t_vm_state *state)
{
	size_t	index;

	index = 0;
	while (index < MEM_SIZE)
	{
		state->memory_info[index].pc_mark = 0;
		index++;
	}
}

int			vm_exec_cycle(t_vm_state *state)
{
	size_t	index;

	log_level(&state->log_info, e_log_cycles,
		"Cycle %d", state->cycle_count + 1);
	index = state->processes.length;
	clear_pc_info(state);
	while (index-- > 0)
		process_exec_cycle(state, index);
	state->cycle_count++;
	return (0);
}

void		vm_state_init(t_vm_state *state)
{
	ft_bzero(state, sizeof(t_vm_state));
	array_init(&state->players, sizeof(t_player));
	array_init(&state->processes, sizeof(t_process));
}

void		player_destroy(void *ptr)
{
	free(((t_player*)ptr)->champion_code);
	((t_player*)ptr)->champion_code = NULL;
}

void		vm_state_clear(t_vm_state *state)
{
	array_clear(&state->processes, NULL);
	array_clear(&state->players, player_destroy);
	logs_destroy(&state->log_info);
}
