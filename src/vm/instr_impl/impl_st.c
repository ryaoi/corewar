/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:05:32 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/16 15:41:31 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"

void	impl_st(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	load_buffer;
	size_t			address;

	if (instr->instr_args[1].arg_type == e_register)
	{
		process->carry = buffer_is_zero(
			process->registers[instr->instr_args[0].arg.reg_index].content,
			REG_SIZE);
		ft_memcpy(
			&process->registers[instr->instr_args[1].arg.reg_index].content.buffer,
			&process->registers[instr->instr_args[0].arg.reg_index].content.buffer,
			REG_SIZE);
	}
	else
	{
		address = *(size_t*)byte_order_swap(
			instr->instr_args[1].arg.index.content, IND_SIZE).buffer;
		ft_memcpy(
			load_buffer.buffer,
			&process->registers[instr->instr_args[0].arg.reg_index].content.buffer,
			REG_SIZE);
		process->carry = buffer_is_zero(load_buffer, REG_SIZE);
		mem_store(state, address, REG_SIZE, load_buffer);
	}
}
