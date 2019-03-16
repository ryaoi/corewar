/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/03/16 19:49:01 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"
#include "libft.h"

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
		{
			(g_impl_table[process->pending_operation.opcode])
				(state, process, &process->pending_operation);
			if (process->pending_operation.opcode != e_zjmp)
				process->program_counter
					= (process->program_counter + new_instr.size) % MEM_SIZE;
		}
		else
			process->program_counter
				= (process->program_counter + 1) % MEM_SIZE;
		new_instr = fetch_instruction(state, process->program_counter);
		process->pending_operation = new_instr;
		process->busy = (new_instr.opcode != e_invalid)
			? g_opcode_table[new_instr.opcode].cycles : 1;
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
