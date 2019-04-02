/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:37:12 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/01 21:51:20 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_sub(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_bigend_buffer	inverted;
	t_process	*process;

	process = &ARRAY_PTR(state->processes, t_process)[p_index];
	(void)state;
	inverted = buffer_invert_bits(
		process->registers[instr->instr_args[1].arg.reg_index - 1].content);
	process->registers[instr->instr_args[2].arg.reg_index - 1].content
		= add_bigend(process->registers[instr->instr_args[0].arg.reg_index - 1].content,
		inverted, 1);
	process->carry = buffer_is_zero(
		process->registers[instr->instr_args[2].arg.reg_index - 1].content);
}
