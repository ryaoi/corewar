/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 18:37:25 by alex              #+#    #+#             */
/*   Updated: 2019/03/19 19:30:45 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"

void	impl_sti(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	first_param;
	t_bigend_buffer	second_param;
	size_t			address;

	if (instr->instr_args[1].arg_type == e_register)
		first_param = process->registers[instr->instr_args[1].arg.reg_index].content;
	else if (instr->instr_args[1].arg_type == e_index)
	{
		address = *byte_order_swap(
			instr->instr_args[1].arg.index.content, IND_SIZE).buffer;
		address = process->program_counter + (address % IDX_MOD);
		/* TODO what size to load? */
		first_param = mem_load(state, address, IND_SIZE);
	}
	else
		first_param = instr->instr_args[1].arg.direct.content;
	if (instr->instr_args[2].arg_type == e_register)
		second_param = process->registers[instr->instr_args[2].arg.reg_index].content;
	else
		second_param = instr->instr_args[2].arg.direct.content;
	address = *byte_order_swap(
		 add_bigend(first_param, second_param, REG_SIZE), REG_SIZE).buffer;
	address = process->program_counter + (address % IDX_MOD);
	mem_store(state, address, REG_SIZE,
		process->registers[instr->instr_args[0].arg.reg_index].content);
}
