/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:14:34 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/01 17:36:57 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bigend_buffer	add_bigend(t_bigend_buffer f, t_bigend_buffer s, uint8_t carry)
{
	uint8_t	new_carry;
	size_t	index;
	t_bigend_buffer	ret;

	ret.buffer = 0;
	index = sizeof(ret.buffer);
	new_carry = 0;
	while (index-- > 0)
	{
		if (((uint8_t*)&f.buffer)[index] > (255 - carry)
			|| (((uint8_t*)&f.buffer)[index] + carry) > (255 - ((uint8_t*)&s.buffer)[index]))
			new_carry = 1;
		else
			new_carry = 0;
		((uint8_t*)&ret.buffer)[index] = ((uint8_t*)&f.buffer)[index] + ((uint8_t*)&s.buffer)[index] + carry;
		carry = new_carry;
	}
	return (ret);
}

void	impl_add(t_vm_state *state, t_process *process, t_instr *instr)
{
	(void)state;
	process->registers[instr->instr_args[2].arg.reg_index - 1].content
		= add_bigend(process->registers[instr->instr_args[0].arg.reg_index - 1].content,
		process->registers[instr->instr_args[1].arg.reg_index - 1].content, 0);
	process->carry = buffer_is_zero(
		process->registers[instr->instr_args[2].arg.reg_index - 1].content);
}
