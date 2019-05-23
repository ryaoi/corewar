/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 14:48:39 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/23 17:15:23 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	fetch_new(t_vm_state *state, size_t p_index)
{
	t_process	*process;

	process = &PROCESS(state, p_index);
	process->pending_operation = fetch_opcode(state, process->program_counter);
	if (process->pending_operation < e_invalid)
		process->busy = g_op_tab[process->pending_operation].cycles;
	else
		process->busy = 1;
}

static void	do_execute(t_vm_state *state, size_t p_index)
{
	t_process	*process;
	t_instr		instr;

	process = &PROCESS(state, p_index);
	process->has_jumped = 0;
	instr = fetch_arguments(state, process->pending_operation,
		process->program_counter);
	if (!instr.invalid)
	{
		log_level(&state->log_info, e_log_instr,
			"Process %d executing %s",
			process->id, g_op_tab[instr.opcode].name);
		(g_impl_table[process->pending_operation])(state, p_index, &instr);
		process = &PROCESS(state, p_index);
	}
	if (!process->has_jumped)
		process->program_counter = (process->program_counter
			+ instr.size) % MEM_SIZE;
}

void		process_exec_cycle(t_vm_state *state, size_t p_index)
{
	t_process	*process;

	process = &PROCESS(state, p_index);
	state->current_process = process;
	state->memory_info[process->program_counter].pc_mark = 1;
	if (process->busy == 0)
		fetch_new(state, p_index);
	if (process->busy >= 1)
		process->busy--;
	if (process->busy == 0)
		do_execute(state, p_index);
}
