/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:14:34 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/18 19:29:27 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bigend_buffer	add_bigend(t_bigend_buffer f, t_bigend_buffer s, size_t size)
{
	uint8_t	old_carry;
	uint8_t	carry;
	size_t	index;
	t_bigend_buffer	ret;

	index = size - 1;
	carry = 0;
	while (index-- > 0)
	{
		if (f.buffer[index] > (255 - old_carry)
			|| (f.buffer[index] + old_carry) > (255 - s.buffer[index]))
			carry = 1;
		else
			carry = 0;
		ret.buffer[index] = f.buffer[index] + s.buffer[index] + old_carry;
		old_carry = carry;
		index++;
	}
	return (ret);
}

void	impl_add(t_vm_state *state, t_process *process, t_instr *instr)
{
	(void)state;
	process->registers[instr->instr_args[2].arg.reg_index].content
		= add_bigend(process->registers[instr->instr_args[0].arg.reg_index].content,
		process->registers[instr->instr_args[1].arg.reg_index].content,
		REG_SIZE);
	process->carry = buffer_is_zero(
		process->registers[instr->instr_args[2].arg.reg_index].content,
		REG_SIZE);
}
