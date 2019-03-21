/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:37:12 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/21 15:51:16 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_sub(t_vm_state *state, t_process *process, t_instr *instr)
{
	(void)state;
	buffer_invert_bits(
		process->registers[instr->instr_args[1].arg.reg_index - 1].content);
	process->registers[instr->instr_args[2].arg.reg_index - 1].content
		= add_bigend(process->registers[instr->instr_args[0].arg.reg_index - 1].content,
		process->registers[instr->instr_args[1].arg.reg_index - 1].content, 1);
	process->carry = buffer_is_zero(
		process->registers[instr->instr_args[2].arg.reg_index - 1].content);
}
