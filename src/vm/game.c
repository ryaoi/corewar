/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:45:28 by aamadori          #+#    #+#             */
/*   Updated: 2019/06/04 15:25:23 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "game.h"

void			prepare_game(t_game_data *game, t_array *players,
					const t_log_info *log_opts)
{
	int	index;

	vm_state_init(&game->state);
	if (log_opts)
		ft_memcpy(&game->state.log_info, log_opts, sizeof(t_log_info));
	index = 0;
	while (index < (int)players->length)
	{
		array_push_back(&game->state.players,
			&((t_player*)players->ptr)[index]);
		index++;
	}
	vm_memory_prepare(&game->state);
	index = 0;
	while (index < (int)players->length)
	{
		vm_init_process(&game->state, ((t_player*)players->ptr)[index].id,
			(MEM_SIZE / players->length) * index);
		index++;
	}
	game->cycles_to_die = CYCLE_TO_DIE;
	game->live_since_dec = 0;
	game->checks_since_dec = 0;
	game->last_check = 0;
}

static t_array	measure_lives(t_game_data *game)
{
	size_t	index;
	t_array	new_array;

	index = 0;
	array_init(&new_array, sizeof(t_process));
	while (index < game->state.processes.length)
	{
		if (process_get(&game->state, index)->live_executed)
		{
			game->live_since_dec += process_get(
					&game->state, index)->live_executed;
			process_get(&game->state, index)->live_executed = 0;
			array_push_back(&new_array, process_get(&game->state, index));
		}
		else
			log_level(&game->state.log_info, e_log_deaths,
				"Process %d smothered!", process_get(&game->state, index)->id);
		index++;
	}
	return (new_array);
}

static void		kill_lazy_processes(t_game_data *game)
{
	t_array	new_array;

	new_array = measure_lives(game);
	array_clear(&game->state.processes, NULL);
	game->state.processes = new_array;
	if (game->checks_since_dec >= MAX_CHECKS
		|| game->live_since_dec >= NBR_LIVE)
	{
		game->cycles_to_die = ft_max(game->cycles_to_die - CYCLE_DELTA, 0);
		log_level(&game->state.log_info, e_log_game,
			"cycles_to_die is now %d", game->cycles_to_die);
		game->checks_since_dec = 0;
		game->live_since_dec = 0;
	}
	else
		game->checks_since_dec++;
}

static void		log_game_over(t_game_data *game)
{
	size_t	index;
	size_t	winner;

	if (game->cycles_to_die <= 0)
		log_level(&game->state.log_info, e_log_game,
			"Game over: cycles_to_die became negative.");
	else
		log_level(&game->state.log_info, e_log_game,
			"Game over: no alive processes.");
	winner = 0;
	index = 1;
	while (index < game->state.players.length)
	{
		if ((player_get(&game->state, index))->live >
			(player_get(&game->state, winner))->live)
			winner = index;
		index++;
	}
	log_level(&game->state.log_info, e_log_game, "Winner: %s, of id %d",
		(player_get(&game->state, winner))->header.prog_name,
		(player_get(&game->state, winner))->id);
}

int				advance_cycle(t_game_data *game)
{
	if (game->cycles_to_die <= 0 || !game->state.processes.length)
	{
		log_game_over(game);
		return (0);
	}
	vm_exec_cycle(&game->state);
	if (game->state.cycle_count - game->last_check
		>= (size_t)game->cycles_to_die)
	{
		kill_lazy_processes(game);
		game->last_check = game->state.cycle_count;
	}
	if (game->cycles_to_die <= 0 || !game->state.processes.length)
	{
		log_game_over(game);
		return (0);
	}
	return (1);
}
