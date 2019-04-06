/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_or.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:41:28 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/06 19:40:15 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_bigend_buffer	bitwise_or(t_bigend_buffer f, t_bigend_buffer s)
{
	t_bigend_buffer	ret;
	size_t			index;

	index = 0;
	while (index < sizeof(f.buffer))
	{
		/* TODO just give up and use size_t internally? */
		INDEX_BUFF(ret, index) = INDEX_BUFF(f, index)
			| INDEX_BUFF(s, index);
		index++;
	}
	return (ret);
}

void					impl_or(t_vm_state *state, size_t p_index,
							t_instr *instr)
{
	t_bigend_buffer	first_operand;
	t_bigend_buffer	second_operand;
	uint32_t			offset;
	t_process	*process;

	process = &PROCESS(state, p_index);
	if (ARG_TYPE(instr, 0) == e_register)
		ft_memcpy(&first_operand,
			&REGISTER(process, ARG_REG(instr, 0)).content,
			sizeof(t_bigend_buffer));
	else if (ARG_TYPE(instr, 0) == e_index)
	{
		offset = byte_order_swap(
			ARG_IND(instr, 0).content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		first_operand = mem_load(state, offset, REG_SIZE);
	}
	else
		ft_memcpy(&first_operand,
			&ARG_DIR(instr, 0).content,
			sizeof(t_bigend_buffer));
	if (ARG_TYPE(instr, 1) == e_register)
		ft_memcpy(&second_operand,
			&REGISTER(process, ARG_REG(instr, 1)).content,
			sizeof(t_bigend_buffer));
	else if (ARG_TYPE(instr, 1) == e_index)
	{
		offset = byte_order_swap(
			ARG_IND(instr, 1).content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		second_operand = mem_load(state, offset, REG_SIZE);
	}
	else
		ft_memcpy(&second_operand,
			&ARG_DIR(instr, 1).content,
			sizeof(t_bigend_buffer));
	REGISTER(process, ARG_REG(instr, 2)).content
		= bitwise_or(first_operand, second_operand);
}
