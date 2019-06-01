/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/06/01 19:43:55 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_aff(t_vm_state *state, size_t p_index, t_instr *instr)
{
	t_bigend_buffer	character_buffer;
	t_process		*process;

	process = process_get(state, p_index);
	character_buffer.buffer = 0;
	(void)state;
	character_buffer = (register_get(process,
				*(arg_reg(instr, 0)) - 1))->content;
	ft_putchar(((uint8_t*)&character_buffer)[REG_SIZE - 1] % 256);
	process->carry = buffer_is_zero(
			(register_get(process, *(arg_reg(instr, 0)) - 1))->content);
}
