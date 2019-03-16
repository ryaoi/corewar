/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:14:34 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/16 15:41:10 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"

void	impl_add(t_vm_state *state, t_process *process, t_instr *instr)
{
	uint8_t	old_carry;
	uint8_t	carry;
	uint8_t a;
	uint8_t	b;
	size_t	index;

	index = REG_SIZE - 1;
	carry = 0;
	while (index-- > 0)
	{
		a = process->registers[instr->instr_args[0].arg.reg_index].content.buffer[index];
		b = process->registers[instr->instr_args[1].arg.reg_index].content.buffer[index];
		carry = (a > (255 - old_carry) || (a + old_carry) > (255 - b)) ? 1 : 0;
		process->registers[instr->instr_args[2].arg.reg_index].content.buffer[index]
			= a + b + old_carry;
		old_carry = carry;
		index++;
	}
	process->carry = buffer_is_zero(
		process->registers[instr->instr_args[2].arg.reg_index].content,
		REG_SIZE);
}