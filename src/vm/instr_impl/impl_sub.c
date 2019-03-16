/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:37:12 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/16 23:39:56 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"
#include "vm.h"

void	impl_sub(t_vm_state *state, t_process *process, t_instr *instr)
{
	buffer_invert_bits(
		process->registers[instr->instr_args[1].arg.reg_index].content,
		REG_SIZE);
	process->registers[instr->instr_args[2].arg.reg_index].content
		= add_bigend(process->registers[instr->instr_args[0].arg.reg_index].content,
		process->registers[instr->instr_args[1].arg.reg_index].content,
		REG_SIZE);
	process->carry = buffer_is_zero(
		process->registers[instr->instr_args[2].arg.reg_index].content,
		REG_SIZE);
}
