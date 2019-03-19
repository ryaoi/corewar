/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_lldi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/19 20:22:04 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_lldi(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	first_param;
	t_bigend_buffer	second_param;
	size_t			address;

	first_param.buffer = 0;
	second_param.buffer = 0;
	if (instr->instr_args[0].arg_type == e_register)
		first_param = process->registers[instr->instr_args[0].arg.reg_index].content;
	else if (instr->instr_args[0].arg_type == e_index)
	{
		address = byte_order_swap(
			instr->instr_args[0].arg.index.content, IND_SIZE).buffer;
		address = process->program_counter + address;
		/* TODO what size to load? */
		first_param = mem_load(state, address, IND_SIZE);
	}
	else
		first_param = instr->instr_args[0].arg.direct.content;
	if (instr->instr_args[1].arg_type == e_register)
		second_param = process->registers[instr->instr_args[1].arg.reg_index].content;
	else
		second_param = instr->instr_args[1].arg.direct.content;
	address = byte_order_swap(
		 add_bigend(first_param, second_param, REG_SIZE), REG_SIZE).buffer;
	address = process->program_counter + address;
	process->registers[instr->instr_args[2].arg.reg_index].content
		= mem_load(state, address, REG_SIZE);
}
