/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:45:28 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/26 18:11:45 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "game.h"

static void	prepare_player(t_player *player, int id)
{
	player->id = id;
	player->live = 0;
}

static void	prepare_game(t_vm_state *state, t_array *players,
				const t_log_info *log_opts)
{
	int	index;

	vm_state_init(state);
	if (log_opts)
		ft_memcpy(&state->log_info, log_opts, sizeof(t_log_info));
	index = 0;
	while (index < (int)players->length)
	{
		prepare_player(&ARRAY_PTR(*players, t_player)[index], -1 - index);
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

static void	kill_lazy_processes(t_vm_state *state, t_game_data *game)
{
	t_list	**traverse;
	t_list	*pop;

	traverse = &state->processes;
	while (*traverse)
	{
		if (!LST_CONT(*traverse, t_process).live_executed
			&& LST_CONT(*traverse, t_process).birth_cycle
				< (state->cycle_count - game->cycles_to_die))
		{
			log_level(&state->log_info, LOG_DEATHS,
				"Process %d smothered!",
				LST_CONT(*traverse, t_process).id);
			pop = list_pop(traverse);
			list_delone(&pop, free_stub);
		}
		else
		{
			game->live_since_dec += LST_CONT(*traverse, t_process).live_executed;
			LST_CONT(*traverse, t_process).live_executed = 0;
			traverse = &((*traverse)->next);
		}
	}
	if (game->checks_since_dec >= MAX_CHECKS || game->live_since_dec >= NBR_LIVE)
	{
		game->cycles_to_die = ft_max(game->cycles_to_die - CYCLE_DELTA, 0);
		game->checks_since_dec = 0;
		game->live_since_dec = 0;
	}
	else
		game->checks_since_dec++;
}

int		play_game(t_array *players, t_vm_state **final, size_t max_cycles,
			const t_log_info *log_opts)
{
	t_vm_state	*state;
	t_game_data	game;
	int			last_check;
	char		game_over;

	if (!(state = malloc(sizeof(t_vm_state))))
		return (-1);
	prepare_game(state, players, log_opts);
	game_over = 0;
	last_check = 0;
	game = (t_game_data){CYCLE_TO_DIE, 0, 0};
	while (game.cycles_to_die > 0 && state->cycle_count < max_cycles && !game_over)
	{
  		vm_exec_cycle(state);
		if ((int)state->cycle_count - last_check >= game.cycles_to_die)
		{
			kill_lazy_processes(state, &game);
			last_check = state->cycle_count;
		}
		if (!state->processes)
			game_over = 1;
	}
	*final = state;
	return (0);
}
