/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/03/19 15:52:21 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	process_exec_cycle(t_vm_state *state, size_t process_index)
{
	t_process	*process;
	t_instr		new_instr;

	process = &ARRAY_PTR(state->processes, t_process)[process_index];
	if (process->busy > 0)
		process->busy--;
	if (process->busy == 0)
	{
		if (process->pending_operation.opcode != e_invalid)
		{
			(g_impl_table[process->pending_operation.opcode])
				(state, process, &process->pending_operation);
		}
		if (!process->pending_operation.is_jump)
			process->program_counter
					= (process->program_counter + new_instr.size) % MEM_SIZE;
		new_instr = fetch_instruction(state, process->program_counter);
		process->pending_operation = new_instr;
		process->busy = (new_instr.opcode != e_invalid)
			? g_opcode_table[new_instr.opcode].cycles : 1;
	}
}

int		vm_exec_cycle(t_vm_state *state)
{
	size_t	process_index;

	process_index = 0;
	while (process_index < state->processes.length)
		process_exec_cycle(state, process_index);
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
	array_init(&state->processes, sizeof(t_process));
}
