/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/15 20:08:53 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"

void	impl_ld(t_vm_state *state, t_process *process, t_instr *instr)
{
	t_bigend_buffer	load_buffer;
	size_t			address;

	if (instr->instr_args[0].arg_type == e_index)
	{
		address = *(size_t*)byte_order_swap(
			instr->instr_args[0].arg.index.content, IND_SIZE).buffer;
		load_buffer = mem_load(state, address, REG_SIZE);
		ft_memcpy(
			&process->registers[instr->instr_args[1].arg.reg_index].content,
			&load_buffer.buffer, REG_SIZE);
	}
	else
	{
		ft_memcpy(
			&process->registers[instr->instr_args[1].arg.reg_index].content,
			&instr->instr_args[0].arg.direct.content,
			ft_min(REG_SIZE, DIR_SIZE)
		);
	}
}
