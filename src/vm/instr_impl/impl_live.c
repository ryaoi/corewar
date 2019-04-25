/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:14:07 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/24 15:49:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_live(t_vm_state *state, size_t p_index, t_instr *instr)
{
	int			parameter;
	size_t		index;
	t_process	*process;

	process = &PROCESS(state, p_index);
	process->live_executed++;
	process->player->last_live_cycle = state->cycle_count;
	parameter = byte_order_swap(
		ARG_DIR(instr, 0).content).buffer;
	index = 0;
	log_level(&state->log_info, e_log_lives,
		"live param: %d, %dnth live on process",
		parameter, process->live_executed);
	while (index < state->players.length)
	{
		if (ARRAY_PTR(state->players, t_player)[index].id == parameter)
		{
			ARRAY_PTR(state->players, t_player)[index].live++;
			break ;
		}
		index++;
	}
}
