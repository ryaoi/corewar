/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/01 21:50:08 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_aff(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_bigend_buffer	character_buffer;
	t_process		*process;

	process = &ARRAY_PTR(state->processes, t_process)[p_index];
	character_buffer.buffer = 0;
	(void)state;
	character_buffer
		= process->registers[instr->instr_args[0].arg.reg_index - 1].content;
	ft_putchar(
		((uint8_t*)&character_buffer)[REG_SIZE - 1] % 256);
	process->carry = buffer_is_zero(
		process->registers[instr->instr_args[0].arg.reg_index - 1].content);
}
