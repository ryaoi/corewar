/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/03/23 17:22:21 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	process_exec_cycle(t_vm_state *state, t_process *process)
{
	t_instr		instr;

	if (process->busy >= 1)
		process->busy--;
	if (process->busy == 0)
	{
		instr = process->pending_operation;
		process->has_jumped = 0;
		if (!instr.invalid)
		{
			(g_impl_table[instr.opcode])(state, process, &instr);
			ft_printf("cycle %d, player %d executing %s\n", state->cycle_count, process->player->id, g_opcode_table[instr.opcode].name);
		}
		if (!process->has_jumped)
			process->program_counter
					= (process->program_counter + instr.size) % MEM_SIZE;
		instr = fetch_instruction(state, process->program_counter);
		process->pending_operation = instr;
		process->busy = instr.cost;
	}
}

int		vm_exec_cycle(t_vm_state *state)
{
	t_list	*traverse;

	traverse = state->processes;
	while (traverse)
	{
		process_exec_cycle(state, &LST_CONT(traverse, t_process));
		traverse = traverse->next;
	}
	state->cycle_count++;
	return (0);
}

void	vm_memory_prepare(t_vm_state *state)
{
	size_t	address;
	size_t	champion;

	ft_bzero(&state->memory, MEM_SIZE);
	champion = 0;
	while (champion < (size_t)ft_min(state->players.length, MAX_PLAYERS))
	{
		address = (MEM_SIZE / state->players.length) * champion;
		ft_memcpy(&state->memory[address],
			ARRAY_PTR(state->players, t_player)[champion].champion_code,
			ARRAY_PTR(state->players, t_player)[champion].header.prog_size);
		champion++;
	}
}

void	vm_state_init(t_vm_state *state)
{
	ft_bzero(state, sizeof(t_vm_state));
	array_init(&state->players, sizeof(t_player));
	state->processes = NULL;
}
