/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:55:16 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/18 19:30:31 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_aff(t_vm_state *state, t_process *process, t_instr *instr)
{
	(void)state;
	ft_putchar(
		process->registers[instr->instr_args[0].arg.reg_index].content.buffer[REG_SIZE - 1] % 256);
	process->carry = buffer_is_zero(
		process->registers[instr->instr_args[0].arg.reg_index].content,
		REG_SIZE);
}
