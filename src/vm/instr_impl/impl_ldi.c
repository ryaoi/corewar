/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/28 14:01:37 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_ldi(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	first_param;
	t_bigend_buffer	second_param;
	int64_t			offset;

	first_param.buffer = 0;
	second_param.buffer = 0;
	if (instr->instr_args[0].arg_type == e_register)
		first_param = process->registers[instr->instr_args[0].arg.reg_index - 1].content;
	else if (instr->instr_args[0].arg_type == e_index)
	{
		offset = byte_order_swap(
			instr->instr_args[0].arg.index.content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		/* TODO what size to load? */
		first_param = mem_load(state, offset, IND_SIZE);
	}
	else
		first_param = instr->instr_args[0].arg.direct.content;
	if (instr->instr_args[1].arg_type == e_register)
		second_param = process->registers[instr->instr_args[1].arg.reg_index - 1].content;
	else
		second_param = instr->instr_args[1].arg.direct.content;
	offset = (int64_t)byte_order_swap(
		 add_bigend(first_param, second_param, 0)).buffer;
	offset = process->program_counter + (offset % IDX_MOD);
	process->registers[instr->instr_args[2].arg.reg_index - 1].content
		= mem_load(state, offset, REG_SIZE);
	log_level(&state->log_info, e_log_load,
		"Storing [%#.8zx] into r%d, val %#.8zx",
		offset,
		instr->instr_args[0].arg.reg_index - 1,
		process->registers[instr->instr_args[2].arg.reg_index - 1].content);
}
