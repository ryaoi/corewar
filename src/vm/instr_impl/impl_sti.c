/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:37:25 by alex              #+#    #+#             */
/*   Updated: 2019/03/20 18:47:17 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_sti(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	first_param;
	t_bigend_buffer	second_param;
	int64_t			offset;

	first_param.buffer = 0;
	second_param.buffer = 0;
	if (instr->instr_args[1].arg_type == e_register)
		first_param = process->registers[instr->instr_args[1].arg.reg_index].content;
	else if (instr->instr_args[1].arg_type == e_index)
	{
		offset = byte_order_swap(
			instr->instr_args[1].arg.index.content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		/* TODO what size to load? */
		first_param = mem_load(state, offset, IND_SIZE);
	}
	else
		first_param = instr->instr_args[1].arg.direct.content;
	if (instr->instr_args[2].arg_type == e_register)
		second_param = process->registers[instr->instr_args[2].arg.reg_index].content;
	else
		second_param = instr->instr_args[2].arg.direct.content;
	offset = (int64_t)byte_order_swap(
		 add_bigend(first_param, second_param, 0)).buffer;
	offset = process->program_counter + (offset % IDX_MOD);
	mem_store(state, offset, REG_SIZE,
		process->registers[instr->instr_args[0].arg.reg_index].content);
}
