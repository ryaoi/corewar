/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:05:32 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/20 17:13:12 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm.h"

void	impl_st(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	load_buffer;
	int64_t			offset;

	load_buffer.buffer = 0;
	if (instr->instr_args[1].arg_type == e_register)
	{
		process->carry = buffer_is_zero(
			process->registers[instr->instr_args[0].arg.reg_index].content);
		process->registers[instr->instr_args[1].arg.reg_index].content
			= process->registers[instr->instr_args[0].arg.reg_index].content;
	}
	else
	{
		offset = byte_order_swap(
			instr->instr_args[1].arg.index.content).buffer;
		offset = process->program_counter + (offset % IDX_MOD);
		load_buffer
			= process->registers[instr->instr_args[0].arg.reg_index].content;
		process->carry = buffer_is_zero(load_buffer);
		mem_store(state, offset, REG_SIZE, load_buffer);
	}
}
