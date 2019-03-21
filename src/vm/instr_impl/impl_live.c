/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:14:07 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/21 18:49:34 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h" /* TODO remove this */

void	impl_live(t_vm_state *state, t_process *process, t_instr *instr)
{
	int		parameter;
	size_t	index;

	process->live_executed++;
	parameter = byte_order_swap(
		instr->instr_args[0].arg.direct.content).buffer;
	/* TODO fix this shit */
	index = 0;
	ft_printf("live param: %d, %dnth live on process\n", parameter, process->live_executed);
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
