/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:40:48 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 17:25:00 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_zjmp(t_vm_state *state, t_process *process, t_instr *instr)
{
	int64_t	offset;

	(void)state;
	if (process->carry)
	{
		offset = byte_order_swap(instr->instr_args[0].arg.direct.content).buffer;
		process->program_counter = (process->program_counter + (offset % IDX_MOD)) % MEM_SIZE;
		process->has_jumped = 1;
		log_level(&state->log_info, e_log_jump,
			"Process %zu zjmp to %zu, TRUE",
			process->id,
			offset);
	}
	else
		log_level(&state->log_info, e_log_jump,
			"Process %zu zjmp to %zu, FALSE",
			process->id,
			offset);
}
