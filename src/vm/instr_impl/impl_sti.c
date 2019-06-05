/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:37:25 by alex              #+#    #+#             */
/*   Updated: 2019/06/05 17:46:31 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_bigend_buffer	sti_first_p(t_vm_state *state,
							t_process *process, t_instr *instr)
{
	t_bigend_buffer	first_p;
	size_t			offset;

	first_p.buffer = 0;
	if (*(arg_type(instr, 1)) == e_register)
		first_p = (register_get(process, *(arg_reg(instr, 1)) - 1))->content;
	else if (*(arg_type(instr, 1)) == e_index)
	{
		offset = byte_order_swap(
			(arg_ind(instr, 1))->content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		first_p = mem_load(state, offset, IND_SIZE);
	}
	else
		first_p = (arg_dir(instr, 1))->content;
	return (first_p);
}

static t_bigend_buffer	sti_second_p(t_vm_state *state,
							t_process *process, t_instr *instr)
{
	t_bigend_buffer	second_p;

	(void)state;
	second_p.buffer = 0;
	if (*(arg_type(instr, 2)) == e_register)
		second_p = (register_get(process, *(arg_reg(instr, 2)) - 1))->content;
	else
		second_p = (arg_dir(instr, 2))->content;
	return (second_p);
}

void					impl_sti(t_vm_state *state, size_t p_index,
							t_instr *instr)
{
	t_process		*process;
	t_bigend_buffer	first_p;
	t_bigend_buffer	second_p;
	int32_t			offset;

	process = process_get(state, p_index);
	first_p = sti_first_p(state, process, instr);
	second_p = sti_second_p(state, process, instr);
	offset = (int32_t)byte_order_swap(
		add_bigend(first_p, second_p, 0)).buffer;
	offset = process->program_counter + (offset % IDX_MOD);
	log_level(&state->log_info, e_log_store,
		"Storing r%d into %#.8zx, val %#.8zx",
		*(arg_reg(instr, 0)),
		offset,
		(register_get(process, *(arg_reg(instr, 0)) - 1))->content);
	mem_store(state, offset, REG_SIZE,
		(register_get(process, *(arg_reg(instr, 0)) - 1))->content);
}
