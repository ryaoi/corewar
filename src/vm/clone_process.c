/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:13:31 by alex              #+#    #+#             */
/*   Updated: 2019/03/21 14:14:27 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_init_process(t_vm_state *state, int player_id, size_t address)
{
	t_process	new_process;

	ft_bzero(&new_process, sizeof(t_process));
	new_process.registers[0].content = byte_order_swap(
		(t_bigend_buffer){(int64_t)player_id});
	new_process.player = &ARRAY_PTR(state->players, t_player)[player_id];
	new_process.program_counter = address;
	new_process.carry = 0;
	new_process.busy = 1;
	new_process.has_jumped = 1;
	instr_init(&new_process.pending_operation);
	new_process.pending_operation.opcode = e_invalid;
	list_add(&state->processes, list_new(&new_process, sizeof(t_process)));
}

void	vm_clone_process(t_vm_state *state, size_t address, t_process *original)
{
	t_process	new_process;

	ft_bzero(&new_process, sizeof(t_process));
	ft_memcpy(new_process.registers, original->registers,
		sizeof(original->registers));
	new_process.program_counter = address;
	new_process.carry = original->carry;
	new_process.busy = 1;
	new_process.player = original->player;
	new_process.has_jumped = 1;
	instr_init(&new_process.pending_operation);
	new_process.pending_operation.opcode = e_invalid;
	list_add(&state->processes, list_new(&new_process, sizeof(t_process)));
}
