/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:41:28 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/01 17:11:59 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_bigend_buffer	bitwise_and(t_bigend_buffer f, t_bigend_buffer s)
{
	t_bigend_buffer	ret;
	size_t			index;

	index = 0;
	while (index < sizeof(f.buffer))
	{
		/* TODO just give up and use size_t internally? */
		((uint8_t*)&ret.buffer)[index] = ((uint8_t*)&f.buffer)[index]
			& ((uint8_t*)&s.buffer)[index];
		index++;
	}
	return (ret);
}

void					impl_and(t_vm_state *state, t_process *process,
							t_instr *instr)
{
	t_bigend_buffer	first_operand;
	t_bigend_buffer	second_operand;
	uint32_t			offset;

	if (instr->instr_args[0].arg_type == e_register)
		ft_memcpy(&first_operand,
			&process->registers[instr->instr_args[0].arg.reg_index].content,
			sizeof(t_bigend_buffer));
	else if (instr->instr_args[0].arg_type == e_index)
	{
		offset = byte_order_swap(
			instr->instr_args[0].arg.index.content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		first_operand = mem_load(state, offset, REG_SIZE);
	}
	else
		ft_memcpy(&first_operand,
			&instr->instr_args[0].arg.direct.content,
			sizeof(t_bigend_buffer));
	if (instr->instr_args[1].arg_type == e_register)
		ft_memcpy(&second_operand,
			&process->registers[instr->instr_args[1].arg.reg_index].content,
			sizeof(t_bigend_buffer));
	else if (instr->instr_args[1].arg_type == e_index)
	{
		offset = byte_order_swap(
			instr->instr_args[1].arg.index.content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		second_operand = mem_load(state, offset, REG_SIZE);
	}
	else
		ft_memcpy(&second_operand,
			&instr->instr_args[1].arg.direct.content,
			sizeof(t_bigend_buffer));
	process->registers[instr->instr_args[2].arg.reg_index].content
		= bitwise_and(first_operand, second_operand);
}
