/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:09:20 by alex              #+#    #+#             */
/*   Updated: 2019/03/31 17:17:59 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_lfork(t_vm_state *state, t_process *process, t_instr *instr)
{
	int64_t	offset;

	offset = byte_order_swap(
		instr->instr_args[0].arg.direct.content).buffer;
	offset = process->program_counter + offset;
	vm_clone_process(state, offset, process);
	log_level(&state->log_info, e_log_fork,
		"Process %zu creates %zu at offset %zu",
		process->id,
		LST_CONT(state->processes, t_process).id,
		offset % MEM_SIZE);
}
