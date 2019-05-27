/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:14:34 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 18:22:57 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bigend_buffer	add_bigend(t_bigend_buffer f, t_bigend_buffer s, uint8_t carry)
{
	uint8_t			new_carry;
	size_t			index;
	t_bigend_buffer	ret;

	ret.buffer = 0;
	index = sizeof(ret.buffer);
	new_carry = 0;
	while (index-- > 0)
	{
		if (*(buff_index(&f, index)) > (255 - carry)
			|| (*(buff_index(&f, index)) + carry)
			> (255 - *(buff_index(&s, index))))
			new_carry = 1;
		else
			new_carry = 0;
		*(buff_index(&ret, index)) = *(buff_index(&f, index))
			+ *(buff_index(&s, index)) + carry;
		carry = new_carry;
	}
	return (ret);
}

void			impl_add(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_process	*process;

	process = process_get(state, p_index);
	(register_get(process, *(arg_reg(instr, 2)) - 1))->content = add_bigend(
		(register_get(process, *(arg_reg(instr, 0)) - 1))->content,
		(register_get(process, *(arg_reg(instr, 1)) - 1))->content, 0);
	process->carry = buffer_is_zero(
		(register_get(process, *(arg_reg(instr, 2)) - 1))->content);
}
