/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/17 00:00:01 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"

void	impl_ldi(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	first_param;
	t_bigend_buffer	second_param;
	size_t			address;

	if (instr->instr_args[0].arg_type == e_register)
		first_param = process->registers[instr->instr_args[0].arg.reg_index].content;
	else if (instr->instr_args[0].arg_type == e_index)
	{
		address = *(size_t*)byte_order_swap(instr->instr_args[0].arg.index.content, IND_SIZE).buffer;
		address = process->program_counter + (address % IDX_MOD);
		/* TODO which size to load? */
		first_param = mem_load(state, address, DIR_SIZE);
	}
	else
	{
		address = *(size_t*)byte_order_swap(instr->instr_args[0].arg.index.content, IND_SIZE).buffer;
		address = process->program_counter + (address % IDX_MOD);
		first_param = byte_order_swap(*(t_bigend_buffer*)address, IND_SIZE);
	}
	if (instr->instr_args[0].arg_type == e_register)
		second_param = process->registers[instr->instr_args[1].arg.reg_index].content;
	else
	{
		address = *(size_t*)byte_order_swap(instr->instr_args[1].arg.index.content, IND_SIZE).buffer;
		address = process->program_counter + (address % IDX_MOD);
		second_param = byte_order_swap(*(t_bigend_buffer*)address, IND_SIZE);
	}
	address = *(size_t*)add_bigend(first_param, second_param, ft_max(REG_SIZE, DIR_SIZE)).buffer;
	address = process->program_counter + (address % IDX_MOD);
	process->registers[instr->instr_args[2].arg.reg_index].content = mem_load(state, address, REG_SIZE);
}
