/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:14:34 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/06 19:41:34 by aamadori         ###   ########.fr       */
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
		if (INDEX_BUFF(f, index) > (255 - carry)
			|| (INDEX_BUFF(f, index) + carry) > (255 - INDEX_BUFF(s, index)))
			new_carry = 1;
		else
			new_carry = 0;
		INDEX_BUFF(ret, index) = INDEX_BUFF(f, index) + INDEX_BUFF(s, index) + carry;
		carry = new_carry;
	}
	return (ret);
}

void	impl_add(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_process	*process;

	process = &PROCESS(state, p_index);
	REGISTER(process, ARG_REG(instr, 2) - 1).content
		= add_bigend(REGISTER(process, ARG_REG(instr, 0) - 1).content,
		REGISTER(process, ARG_REG(instr, 1) - 1).content, 0);
	process->carry = buffer_is_zero(
		REGISTER(process, ARG_REG(instr, 2) - 1).content);
}
