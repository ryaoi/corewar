/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:05:32 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/06 19:08:09 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm.h"

void	impl_st(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_bigend_buffer	load_buffer;
	int32_t			offset;
	t_process	*process;

	process = &ARRAY_PTR(state->processes, t_process)[p_index];
	load_buffer.buffer = 0;
	if (ARG_TYPE(instr, 1) == e_register)
	{
		process->carry = buffer_is_zero(
			REGISTER(process, ARG_REG(instr, 0) - 1).content);
		REGISTER(process, ARG_REG(instr, 1) - 1).content
			= REGISTER(process, ARG_REG(instr, 0) - 1).content;
		log_level(&state->log_info, e_log_store,
			"Storing r%d into r%d, val %#.8zx",
			ARG_REG(instr, 0) - 1,
			ARG_REG(instr, 1) - 1,
			REGISTER(process, ARG_REG(instr, 0) - 1).content);
	}
	else
	{
		offset = byte_order_swap(
			ARG_IND(instr, 1).content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		load_buffer
			= REGISTER(process, ARG_REG(instr, 0) - 1).content;
		process->carry = buffer_is_zero(load_buffer);
		mem_store(state, offset, REG_SIZE, load_buffer);
		log_level(&state->log_info, e_log_store,
			"Storing r%d into %#.8zx, val %#.8zx",
			ARG_REG(instr, 0) - 1,
			offset,
			REGISTER(process, ARG_REG(instr, 0) - 1).content);
	}
}
