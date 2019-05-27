/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:14:07 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 18:39:51 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_live(t_vm_state *state, size_t p_index, t_instr *instr)
{
	int			parameter;
	size_t		index;
	t_process	*process;

	process = process_get(state, p_index);
	process->live_executed++;
	parameter = byte_order_swap(
		(arg_dir(instr, 0))->content).buffer;
	index = 0;
	log_level(&state->log_info, e_log_lives,
		"live param: %d, %dnth live on process",
		parameter, process->live_executed);
	while (index < state->players.length)
	{
		if ((player_get(state, index))->id == parameter)
		{
			(player_get(state, index))->last_live_cycle = state->cycle_count;
			(player_get(state, index))->live++;
			break ;
		}
		index++;
	}
}
