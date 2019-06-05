/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:05:32 by aamadori          #+#    #+#             */
/*   Updated: 2019/06/05 17:45:37 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm.h"

static void	st_register(t_vm_state *state, t_process *process, t_instr *instr)
{
	(register_get(process,
			*(arg_reg(instr, 1)) - 1))->content = (register_get(process,
				*(arg_reg(instr, 0)) - 1))->content;
	log_level(&state->log_info, e_log_store,
		"Storing r%d into r%d, val %#.8zx",
		*(arg_reg(instr, 0)), *(arg_reg(instr, 1)),
		(register_get(process, *(arg_reg(instr, 0)) - 1))->content);
}

static void	st_index(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	load_buffer;
	int32_t			offset;

	load_buffer.buffer = 0;
	offset = byte_order_swap((arg_ind(instr, 1)->content)).buffer;
	offset = process->program_counter + (offset % IDX_MOD);
	load_buffer = (register_get(process, *(arg_reg(instr, 0)) - 1))->content;
	mem_store(state, offset, REG_SIZE, load_buffer);
	log_level(&state->log_info, e_log_store,
		"Storing r%d into %#.8zx, val %#.8zx",
		*(arg_reg(instr, 0)), offset,
		(register_get(process, *(arg_reg(instr, 0)) - 1))->content);
}

void		impl_st(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_process	*process;

	process = process_get(state, p_index);
	if (*(arg_type(instr, 1)) == e_register)
		st_register(state, process, instr);
	else
		st_index(state, process, instr);
}
