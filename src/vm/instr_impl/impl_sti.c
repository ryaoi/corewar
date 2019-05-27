/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:37:25 by alex              #+#    #+#             */
/*   Updated: 2019/05/27 18:14:54 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_bigend_buffer	sti_first_p(t_vm_state *state,
							t_process *process, t_instr *instr)
{
	t_bigend_buffer	first_param;
	size_t			offset;

	first_param.buffer = 0;
	if (*(arg_type(instr, 1)) == e_register)
		first_param = (register_get(process, *(arg_reg(instr, 1)) - 1))->content;
	else if (*(arg_type(instr, 1)) == e_index)
	{
		offset = byte_order_swap(
			(arg_ind(instr, 1))->content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		first_param = mem_load(state, offset, IND_SIZE);
	}
	else
		first_param = (arg_dir(instr, 1))->content;
	return (first_param);
}

static t_bigend_buffer	sti_second_p(t_vm_state *state,
							t_process *process, t_instr *instr)
{
	t_bigend_buffer	second_param;

	(void)state;
	second_param.buffer = 0;
	if (*(arg_type(instr, 2)) == e_register)
		second_param = (register_get(process, *(arg_reg(instr, 2)) - 1))->content;
	else
		second_param = (arg_dir(instr, 2))->content;
	return (second_param);
}

void					impl_sti(t_vm_state *state, size_t p_index,
							t_instr *instr)
{
	t_process		*process;
	t_bigend_buffer	first_param;
	t_bigend_buffer	second_param;
	int32_t			offset;

	process = process_get(state, p_index);
	first_param = sti_first_p(state, process, instr);
	second_param = sti_second_p(state, process, instr);
	offset = (int32_t)byte_order_swap(
		add_bigend(first_param, second_param, 0)).buffer;
	offset = process->program_counter + (offset % IDX_MOD);
	log_level(&state->log_info, e_log_store,
		"Storing r%d into %#.8zx, val %#.8zx",
		*(arg_reg(instr, 0)) - 1,
		offset,
		(register_get(process, *(arg_reg(instr, 0)) - 1))->content);
	mem_store(state, offset, REG_SIZE,
		(register_get(process, *(arg_reg(instr, 0)) - 1))->content);
}
