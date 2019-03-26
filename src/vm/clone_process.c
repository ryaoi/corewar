/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:13:31 by alex              #+#    #+#             */
/*   Updated: 2019/03/26 11:43:50 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

size_t	vm_new_id(t_vm_state *state)
{
	return (state->process_count++);
}

void	vm_init_process(t_vm_state *state, int player_id, size_t address)
{
	t_process	new_process;
	size_t		search;

	ft_bzero(&new_process, sizeof(t_process));
	new_process.registers[0].content = byte_order_swap(
		(t_bigend_buffer){(int64_t)player_id});
	search = 0;
	/* TODO error check */
	while (search < state->players.length)
	{
		if (ARRAY_PTR(state->players, t_player)[search].id == player_id)
		{
			new_process.player = &ARRAY_PTR(state->players, t_player)[search];
			break ;
		}
		search++;
	}
	new_process.program_counter = address;
	new_process.has_jumped = 1;
	new_process.id = vm_new_id(state);
	new_process.pending_operation = fetch_opcode(state, new_process.program_counter);
	new_process.birth_cycle = state->cycle_count;
	if (new_process.pending_operation < e_invalid)
		new_process.busy = g_opcode_table[new_process.pending_operation].cycles;
	else
		new_process.busy = 1;
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
	new_process.player = original->player;
	new_process.has_jumped = 1;
	new_process.id = vm_new_id(state);
	new_process.pending_operation = fetch_opcode(state, new_process.program_counter);
	new_process.birth_cycle = state->cycle_count;
	if (new_process.pending_operation < e_invalid)
		new_process.busy = g_opcode_table[new_process.pending_operation].cycles;
	else
		new_process.busy = 1;
	list_add(&state->processes, list_new(&new_process, sizeof(t_process)));
}
