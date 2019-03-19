/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/19 20:21:51 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_lld(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	load_buffer;
	size_t			address;

	load_buffer.buffer = 0;
	if (instr->instr_args[0].arg_type == e_index)
	{
		address = byte_order_swap(
			instr->instr_args[0].arg.index.content, IND_SIZE).buffer;
		address = process->program_counter + address;
		load_buffer = mem_load(state, address, REG_SIZE);
		process->carry = buffer_is_zero(load_buffer, REG_SIZE);
		ft_memcpy(
			&process->registers[instr->instr_args[1].arg.reg_index].content.buffer,
			&load_buffer.buffer,
			REG_SIZE);
	}
	else
	{
		process->carry = buffer_is_zero(
			instr->instr_args[0].arg.direct.content, DIR_SIZE);
		ft_memcpy(
			&process->registers[instr->instr_args[1].arg.reg_index].content.buffer,
			&instr->instr_args[0].arg.direct.content.buffer,
			ft_min(REG_SIZE, DIR_SIZE));
	}
}
