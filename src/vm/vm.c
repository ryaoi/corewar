/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2019/03/31 18:26:14 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int		vm_exec_cycle(t_vm_state *state)
{
	t_list	*traverse;
	log_level(&state->log_info, e_log_cycles,
		"Cycle %d", state->cycle_count + 1);
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

static void	player_destroy(void *ptr)
{
	t_player *player;

	player = ptr;
	free(player->champion_code);
	player->champion_code = NULL;
}

static void	process_free(void *ptr, size_t stub)
{
	t_process *process;

	(void)stub;
	process = ptr;
	process->player = NULL;
	free(process);
}

void	vm_state_clear(t_vm_state *state)
{
	array_clear(&state->players, player_destroy);
	list_del(&state->processes, process_free);
	logs_destroy(&state->log_info);
}
