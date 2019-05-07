/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_xor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 15:41:28 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/17 17:23:48 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_bigend_buffer	bitwise_xor(t_bigend_buffer f, t_bigend_buffer s)
{
	t_bigend_buffer	ret;

	ret.buffer = f.buffer ^ s.buffer;
	return (ret);
}

static t_bigend_buffer	handle_argument(t_vm_state *state, t_process *process,
							t_instr *instr, size_t arg_index)
{
	t_bigend_buffer	ret;
	size_t			offset;

	if (ARG_TYPE(instr, arg_index) == e_register)
		ft_memcpy(&ret,
			&REGISTER(process, ARG_REG(instr, arg_index)).content,
			sizeof(t_bigend_buffer));
	else if (ARG_TYPE(instr, arg_index) == e_index)
	{
		offset = byte_order_swap(
			ARG_IND(instr, arg_index).content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		ret = mem_load(state, offset, REG_SIZE);
	}
	else
		ft_memcpy(&ret,
			&ARG_DIR(instr, arg_index).content,
			sizeof(t_bigend_buffer));
	return (ret);
}

void					impl_xor(t_vm_state *state, size_t p_index,
							t_instr *instr)
{
	t_bigend_buffer	first_operand;
	t_bigend_buffer	second_operand;
	t_process		*process;

	process = &PROCESS(state, p_index);
	first_operand = handle_argument(state, process, instr, 0);
	second_operand = handle_argument(state, process, instr, 1);
	REGISTER(process, ARG_REG(instr, 2) - 1).content = bitwise_xor(
		first_operand, second_operand);
	process->carry = buffer_is_zero(
		REGISTER(process, ARG_REG(instr, 2) - 1).content);
}