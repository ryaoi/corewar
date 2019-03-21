/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:14:07 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/21 14:05:55 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_live(t_vm_state *state, t_process *process, t_instr *instr)
{
	int		parameter;
	size_t	index;

	process->live_executed++;
	parameter = byte_order_swap(
		instr->instr_args[0].arg.direct.content).buffer;
	/* TODO fix this shit */
	index = 0;
	while (index < state->players.length)
	{
		if (ARRAY_PTR(state->players, t_player)[index].id == parameter)
			ARRAY_PTR(state->players, t_player)[index].live++;
		index++;
	}
}
