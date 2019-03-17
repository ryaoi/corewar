/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:13:31 by alex              #+#    #+#             */
/*   Updated: 2019/03/17 19:30:33 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void    vm_spawn_player(t_vm_state *state, size_t address, t_process *original)
{
	t_process	new_process;

	ft_bzero(&new_process, sizeof(t_process));
	ft_memcpy(new_process.registers, original->registers,
		sizeof(original->registers));
	new_process.program_counter = address;
	new_process.carry = original->carry;
	new_process.id = state->processes.length;
	new_process.live = 0;
	new_process.busy = 1;
	instr_init(&new_process.pending_operation);
	new_process.pending_operation.opcode = e_invalid;
	new_process.pending_operation.is_jump = 1;
	new_process.owner = original->owner;
	array_push_back(&state->processes, &new_process);
}