/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:37:12 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/17 17:35:06 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_sub(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_bigend_buffer	inverted;
	t_process		*process;

	process = &PROCESS(state, p_index);
	(void)state;
	inverted = buffer_invert_bits(
		REGISTER(process, ARG_REG(instr, 1) - 1).content);
	REGISTER(process, ARG_REG(instr, 2) - 1).content = add_bigend(
		REGISTER(process, ARG_REG(instr, 0) - 1).content,
		inverted, 1);
	process->carry = buffer_is_zero(
		REGISTER(process, ARG_REG(instr, 2) - 1).content);
}
