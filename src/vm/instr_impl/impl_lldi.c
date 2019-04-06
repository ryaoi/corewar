/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/06 19:08:09 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_lldi(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_bigend_buffer	first_param;
	t_bigend_buffer	second_param;
	int32_t			offset;
	t_process	*process;

	process = &ARRAY_PTR(state->processes, t_process)[p_index];
	first_param.buffer = 0;
	second_param.buffer = 0;
	if (ARG_TYPE(instr, 0) == e_register)
		first_param = REGISTER(process, ARG_REG(instr, 0) - 1).content;
	else if (ARG_TYPE(instr, 0) == e_index)
	{
		offset = byte_order_swap(
			ARG_IND(instr, 0).content).buffer;
		offset = process->program_counter + offset;
		/* TODO what size to load? */
		first_param = mem_load(state, offset, IND_SIZE);
	}
	else
		first_param = ARG_DIR(instr, 0).content;
	if (ARG_TYPE(instr, 1) == e_register)
		second_param = REGISTER(process, ARG_REG(instr, 1) - 1).content;
	else
		second_param = ARG_DIR(instr, 1).content;
	offset = (int64_t)byte_order_swap(
		 add_bigend(first_param, second_param, 0)).buffer;
	offset = process->program_counter + offset;
	REGISTER(process, ARG_REG(instr, 2) - 1).content
		= mem_load(state, offset, REG_SIZE);
	log_level(&state->log_info, e_log_load,
		"Storing [%#.8zx] into r%d, val %#.8zx",
		offset % MEM_SIZE,
		ARG_REG(instr, 2) - 1,
		REGISTER(process, ARG_REG(instr, 2) - 1).content);
}
