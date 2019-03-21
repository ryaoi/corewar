/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:45:28 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/21 15:45:28 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	prepare_player(t_player *player, int id)
{
	player->id = id;
	player->live = 0;
}

static void	prepare_game(t_vm_state *state, t_array *players)
{
	int	index;

	vm_state_init(state);
	index = 0;
	while (index < (int)players->length)
	{
		prepare_player(&ARRAY_PTR(*players, t_player)[index], -index);
		array_push_back(&state->players, &ARRAY_PTR(*players, t_player)[index]);
		index++;
	}
	vm_memory_prepare(state);
	index = 0;
	while (index < (int)players->length)
	{
		vm_init_process(state, -1 - index, (MEM_SIZE / players->length) * index);
		index++;
	}
}

/* static void	clear_game(t_vm_state *state)
{
	array_clear(&state->players, NULL);
	list_del(&state->processes, free_stub);
	free(state);
} */

static void	kill_lazy_processes(t_vm_state *state, int *cycles_to_die, int *checks)
{
	t_list	**traverse;
	t_list	*pop;
	int		lived_count;

	lived_count = 0;
	traverse = &state->processes;
	while (*traverse)
	{
		if (!LST_CONT(*traverse, t_process).live_executed)
		{
			/* TODO list pop? */
			pop = list_pop(traverse);
			list_delone(&pop, free_stub);
		}
		else
		{
			lived_count += LST_CONT(*traverse, t_process).live_executed;
			LST_CONT(*traverse, t_process).live_executed = 0;
			traverse = &((*traverse)->next);
		}
	}
	if (*checks >= MAX_CHECKS || lived_count >= NBR_LIVE)
	{
		*cycles_to_die = ft_max(*cycles_to_die - CYCLE_DELTA, 0);
		*checks = 0;
	}
	else
		(*checks)++;
}

int		play_game(t_array *players, t_vm_state **final, size_t max_cycles)
{
	t_vm_state	*state;
	int			cycles_to_die;
	int			last_die;
	int			checks_since_dec;
	char		game_over;

	if (!(state = malloc(sizeof(t_vm_state))))
		return (-1);
	prepare_game(state, players);
	game_over = 0;
	cycles_to_die = CYCLE_TO_DIE;
	last_die = 0;
	checks_since_dec = 0;
	while (cycles_to_die > 0 && state->cycle_count < max_cycles && !game_over)
	{
		vm_exec_cycle(state);
		if ((int)state->cycle_count - last_die >= cycles_to_die)
		{
			kill_lazy_processes(state, &cycles_to_die, &checks_since_dec);
			last_die = state->cycle_count;
		}
		if (!state->processes)
			game_over = 1;
	}
	*final = state;
	return (0);
}
