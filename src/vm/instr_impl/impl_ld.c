/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/06 19:08:09 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_ld(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_bigend_buffer	load_buffer;
	int32_t			offset;
	t_process		*process;

	process = &ARRAY_PTR(state->processes, t_process)[p_index];
	load_buffer.buffer = 0;
	if (ARG_TYPE(instr, 0) == e_index)
	{
		offset = byte_order_swap(
			ARG_IND(instr, 0).content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		load_buffer = mem_load(state, offset, REG_SIZE);
		process->carry = buffer_is_zero(load_buffer);
		REGISTER(process, ARG_REG(instr, 1) - 1).content
				= load_buffer;
		log_level(&state->log_info, e_log_load,
			"Storing [%#.8zx] into r%d, val %#.8zx",
			offset % MEM_SIZE,
			ARG_REG(instr, 1) - 1,
			REGISTER(process, ARG_REG(instr, 1) - 1).content);
	}
	else
	{
		process->carry = buffer_is_zero(
			ARG_DIR(instr, 0).content);
		REGISTER(process, ARG_REG(instr, 1) - 1).content
			= ARG_DIR(instr, 0).content;
		log_level(&state->log_info, e_log_load,
			"Storing direct into r%d, val %#.8zx",
			ARG_REG(instr, 1) - 1,
			REGISTER(process, ARG_REG(instr, 1) - 1).content);
	}
}
