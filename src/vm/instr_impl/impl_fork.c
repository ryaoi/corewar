/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:09:20 by alex              #+#    #+#             */
/*   Updated: 2019/05/27 17:58:15 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_fork(t_vm_state *state, size_t p_index, t_instr *instr)
{
	int32_t	offset;

	offset = byte_order_swap(
		(arg_dir(instr, 0)->content)).buffer;
	offset = process_get(state, p_index)->program_counter
		+ (offset % IDX_MOD);
	vm_clone_process(state, offset, process_get(state, p_index));
	log_level(&state->log_info, e_log_fork,
		"Process %zu creates %zu at offset %zu",
		process_get(state, p_index)->id,
		ARRAY_PTR(state->processes, t_process)[state->processes.length - 1].id,
		offset % MEM_SIZE);
}
