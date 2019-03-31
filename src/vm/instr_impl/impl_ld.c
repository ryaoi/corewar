/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 17:17:18 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_ld(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	load_buffer;
	int64_t			offset;

	load_buffer.buffer = 0;
	if (instr->instr_args[0].arg_type == e_index)
	{
		offset = byte_order_swap(
			instr->instr_args[0].arg.index.content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		load_buffer = mem_load(state, offset, REG_SIZE);
		process->carry = buffer_is_zero(load_buffer);
		process->registers[instr->instr_args[1].arg.reg_index - 1].content
				= load_buffer;
		log_level(&state->log_info, e_log_load,
			"Storing [%#.8zx] into r%d, val %#.8zx",
			offset % MEM_SIZE,
			instr->instr_args[1].arg.reg_index - 1,
			process->registers[instr->instr_args[1].arg.reg_index - 1].content);
	}
	else
	{
		process->carry = buffer_is_zero(
			instr->instr_args[0].arg.direct.content);
		process->registers[instr->instr_args[1].arg.reg_index - 1].content
			= instr->instr_args[0].arg.direct.content;
		log_level(&state->log_info, e_log_load,
			"Storing direct into r%d, val %#.8zx",
			instr->instr_args[1].arg.reg_index - 1,
			process->registers[instr->instr_args[1].arg.reg_index - 1].content);
	}
}
