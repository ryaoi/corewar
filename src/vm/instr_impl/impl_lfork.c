/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:09:20 by alex              #+#    #+#             */
/*   Updated: 2019/04/06 19:01:24 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_lfork(t_vm_state *state, size_t p_index, t_instr *instr)
{
	int32_t	offset;

	offset = byte_order_swap(
		ARG_DIR(instr, 0).content).buffer;
	offset = ARRAY_PTR(state->processes, t_process)[p_index].program_counter + offset;
	vm_clone_process(state, offset, &ARRAY_PTR(state->processes, t_process)[p_index]);
	log_level(&state->log_info, e_log_fork,
		"Process %zu creates %zu at offset %zu",
		ARRAY_PTR(state->processes, t_process)[p_index].id,
		ARRAY_PTR(state->processes, t_process)[state->processes.length - 1].id,
		offset % MEM_SIZE);
}
