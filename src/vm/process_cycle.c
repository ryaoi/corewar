/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:48:39 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/01 21:55:18 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	process_exec_cycle(t_vm_state *state, size_t p_index)
{
	t_instr		instr;
	t_process	*process;

	process = &ARRAY_PTR(state->processes, t_process)[p_index];
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
				(state, p_index, &instr);
			process = &ARRAY_PTR(state->processes, t_process)[p_index];
		}
		if (!process->has_jumped)
			process->program_counter
				= (process->program_counter + instr.size) % MEM_SIZE;
	}
}
