/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:13:31 by alex              #+#    #+#             */
/*   Updated: 2019/03/19 19:36:31 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_init_process(t_vm_state *state, size_t player_id)
{
	t_process	new_process;

	ft_bzero(&new_process, sizeof(t_process));
	new_process.registers[0].content = byte_order_swap(
		(t_bigend_buffer){player_id}, REG_SIZE);
	new_process.player = &ARRAY_PTR(state->players, t_player)[player_id];
	new_process.program_counter = (MEM_SIZE / state->players.length) * player_id;
	new_process.carry = 0;
	new_process.id = state->processes.length;
	new_process.busy = 1;
	instr_init(&new_process.pending_operation);
	new_process.pending_operation.opcode = e_invalid;
	new_process.pending_operation.is_jump = 1;
	array_push_back(&state->processes, &new_process);
}

void	vm_clone_process(t_vm_state *state, size_t address, t_process *original)
{
	t_process	new_process;

	ft_bzero(&new_process, sizeof(t_process));
	ft_memcpy(new_process.registers, original->registers,
		sizeof(original->registers));
	new_process.program_counter = address;
	new_process.carry = original->carry;
	new_process.id = state->processes.length;
	new_process.busy = 1;
	new_process.player = original->player;
	instr_init(&new_process.pending_operation);
	new_process.pending_operation.opcode = e_invalid;
	new_process.pending_operation.is_jump = 1;
	array_push_back(&state->processes, &new_process);
}
