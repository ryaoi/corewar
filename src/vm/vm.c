/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/03/25 18:31:54 by aamadori         ###   ########.fr       */
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
		process->has_jumped = 0;
		instr = fetch_arguments(state, process->pending_operation,
			process->program_counter);
		if (!instr.invalid)
		{
			ft_printf("Process %d executing %s\n", process->id, g_opcode_table[instr.opcode].name);
			(g_impl_table[process->pending_operation])
				(state, process, &instr);
		}
		if (!process->has_jumped)
			process->program_counter
					= (process->program_counter + instr.size) % MEM_SIZE;
		process->pending_operation = fetch_opcode(state, process->program_counter);
		if (process->pending_operation < e_invalid)
			process->busy = g_opcode_table[process->pending_operation].cycles;
		else
			process->busy = 1;
	}
}

int		vm_exec_cycle(t_vm_state *state)
{
	t_list	*traverse;

	ft_printf("Cycle %d\n", state->cycle_count + 1);
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
	state->process_count = 1;
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
