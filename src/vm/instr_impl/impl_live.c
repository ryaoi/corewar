/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:14:07 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/01 21:50:53 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_live(t_vm_state *state, size_t p_index, t_instr *instr)
{
	int			parameter;
	size_t		index;
	t_process	*process;

	process = &ARRAY_PTR(state->processes, t_process)[p_index];
	process->live_executed++;
	parameter = byte_order_swap(
		instr->instr_args[0].arg.direct.content).buffer;
	index = 0;
	log_level(&state->log_info, e_log_lives,
		"live param: %d, %dnth live on process",
		parameter, process->live_executed);
	while (index < state->players.length)
	{
		if (ARRAY_PTR(state->players, t_player)[index].id == parameter)
		{
			ARRAY_PTR(state->players, t_player)[index].live++;
			break;
		}
		index++;
	}
}
