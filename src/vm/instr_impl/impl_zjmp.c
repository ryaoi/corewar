/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:40:48 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/19 16:35:48 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_zjmp(t_vm_state *state, size_t p_index, t_instr *instr)
{
	int32_t		offset;
	t_process	*process;

	process = &PROCESS(state, p_index);
	offset = byte_order_swap(ARG_DIR(instr, 0).content).buffer;
	if (process->carry)
	{
		state->memory_info[process->program_counter].pc_count--;
		process->program_counter = (process->program_counter
			+ (offset % IDX_MOD)) % MEM_SIZE;
		state->memory_info[process->program_counter].pc_count++;
		process->has_jumped = 1;
		log_level(&state->log_info, e_log_jump,
			"Process %zu zjmp to %zu, TRUE",
			process->id,
			offset);
	}
	else
		log_level(&state->log_info, e_log_jump,
			"Process %zu zjmp to %zu, FALSE",
			process->id,
			offset);
}
