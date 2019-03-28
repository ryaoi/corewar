/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:48:39 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/28 14:02:02 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	process_exec_cycle(t_vm_state *state, t_process *process)
{
	t_instr		instr;

	if (process->busy == 0)
	{
		process->pending_operation = fetch_opcode(state, process->program_counter);
		if (process->pending_operation < e_invalid)
			process->busy = g_opcode_table[process->pending_operation].cycles;
		else
			process->busy = 1;
	}
	if (process->busy >= 1)
		process->busy--;
	if (process->busy == 0)
	{
		process->has_jumped = 0;
		instr = fetch_arguments(state, process->pending_operation,
			process->program_counter);
		if (!instr.invalid)
		{
			log_level(&state->log_info, e_log_instr,
				"Process %d executing %s",
				process->id, g_opcode_table[instr.opcode].name);
			(g_impl_table[process->pending_operation])
				(state, process, &instr);
		}
		if (!process->has_jumped)
			process->program_counter
				= (process->program_counter + instr.size) % MEM_SIZE;
	}
}
