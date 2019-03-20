/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/03/20 17:16:27 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void	process_exec_cycle(t_vm_state *state, size_t process_index)
{
	t_process	**processes;
	t_instr		instr;

	processes = (t_process**)&state->processes.ptr;
	if ((*processes)[process_index].busy > 1)
		(*processes)[process_index].busy--;
	if ((*processes)[process_index].busy == 1)
	{
		instr = (*processes)[process_index].pending_operation;
		(*processes)[process_index].has_jumped = 0;
		if (instr.opcode != e_invalid)
		{
			(g_impl_table[instr.opcode])
				(state, &(*processes)[process_index], &instr);
		}
		if (!(*processes)[process_index].has_jumped)
			(*processes)[process_index].program_counter
					= ((*processes)[process_index].program_counter + instr.size) % MEM_SIZE;
		instr = fetch_instruction(state, (*processes)[process_index].program_counter);
		(*processes)[process_index].pending_operation = instr;
		(*processes)[process_index].busy = (instr.opcode != e_invalid)
			? g_opcode_table[instr.opcode].cycles : 1;
	}
}

int		vm_exec_cycle(t_vm_state *state)
{
	size_t	process_index;

	process_index = state->processes.length;
	while (process_index-- > 0)
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
