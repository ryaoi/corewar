/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:09:20 by alex              #+#    #+#             */
/*   Updated: 2019/03/20 15:22:29 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_lfork(t_vm_state *state, t_process *process, const t_instr *instr)
{
	int64_t	offset;

	offset = byte_order_swap(
		instr->instr_args[0].arg.direct.content).buffer;
	offset = process->program_counter + offset;
	vm_clone_process(state, offset, process);
}
