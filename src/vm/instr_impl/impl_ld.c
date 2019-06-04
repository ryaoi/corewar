/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/06/04 14:55:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	load_index(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	load_buffer;
	int32_t			offset;

	load_buffer.buffer = 0;
	offset = byte_order_swap(
		(arg_ind(instr, 0))->content).buffer;
	offset = process->program_counter + (offset % IDX_MOD);
	load_buffer = mem_load(state, offset, REG_SIZE);
	process->carry = buffer_is_zero(load_buffer);
	(register_get(process,
		*(arg_reg(instr, 1)) - 1))->content = load_buffer;
	log_level(&state->log_info, e_log_load,
		"Loading [%#.8zx] into r%d, val %#.8zx",
		offset % MEM_SIZE,
		*(arg_reg(instr, 1)) - 1,
		(register_get(process, *(arg_reg(instr, 1)) - 1))->content);
}

static void	load_direct(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	load_buffer;

	load_buffer.buffer = 0;
	process->carry = buffer_is_zero(
		(arg_dir(instr, 0))->content);
	(register_get(process,
		*(arg_reg(instr, 1)) - 1))->content = (arg_dir(instr, 0))->content;
	log_level(&state->log_info, e_log_load,
		"Loading direct into r%d, val %#.8zx",
		*(arg_reg(instr, 1)) - 1,
		(register_get(process, *(arg_reg(instr, 1)) - 1))->content);
}

void		impl_ld(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_process		*process;

	process = process_get(state, p_index);
	if (*(arg_type(instr, 0)) == e_index)
		load_index(state, process, instr);
	else
		load_direct(state, process, instr);
}
