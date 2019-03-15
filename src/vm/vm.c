/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/03/15 16:42:01 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"

int		process_exec_cycle(t_vm_state *state, size_t process_index)
{
	t_process	*process;
	t_instr		new_instr;

	process = &ARRAY_PTR(state->processes, t_process)[process_index];
	if (process->busy > 0)
		process->busy--;
	if (process->busy == 0)
	{
		if (process->pending_operation.opcode != e_invalid)
			(g_impl_table[process->pending_operation.opcode])(state, process);
		new_instr = fetch_instruction(state, process->program_counter);
		if (new_instr.opcode == e_invalid)
		{
			process->pending_operation.opcode = e_invalid;
			process->busy = 1;
			process->program_counter
				= (process->program_counter + 1) % MEM_SIZE;
		}
		else
		{
			process->pending_operation = new_instr;
			process->busy = g_opcode_table[new_instr.opcode].cycles;
			process->program_counter
				= (process->program_counter + new_instr.size) % MEM_SIZE;
		}
	}
}

int		vm_exec_cycle(t_vm_state *state)
{
	size_t	process_index;

	process_index = 0;
	while (process_index < state->processes.length)
	{
		if (process_exec_cycle(state, process_index) < 0)
			return (-1);
	}
	return (0);
}
