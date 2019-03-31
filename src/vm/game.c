/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:45:28 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 16:46:16 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "game.h"

static void	prepare_player(t_player *player, int id)
{
	player->id = id;
	player->live = 0;
}

void	prepare_game(t_game_data *game, t_array *players,
			const t_log_info *log_opts)
{
	int	index;

	vm_state_init(&game->state);
	if (log_opts)
		ft_memcpy(&game->state.log_info, log_opts, sizeof(t_log_info));
	index = 0;
	while (index < (int)players->length)
	{
		prepare_player(&ARRAY_PTR(*players, t_player)[index], -1 - index);
		array_push_back(&game->state.players, &ARRAY_PTR(*players, t_player)[index]);
		index++;
	}
	vm_memory_prepare(&game->state);
	index = 0;
	while (index < (int)players->length)
	{
		vm_init_process(&game->state, -1 - index, (MEM_SIZE / players->length) * index);
			index++;
	}
	game->cycles_to_die = CYCLE_TO_DIE;
	game->live_since_dec = 0;
	game->checks_since_dec = 0;
}

static void	kill_lazy_processes(t_game_data *game)
{
	t_list	**traverse;
	t_list	*pop;

	traverse = &game->state.processes;
	while (*traverse)
	{
		if (!LST_CONT(*traverse, t_process).live_executed
			&& LST_CONT(*traverse, t_process).birth_cycle
				< (game->state.cycle_count - game->cycles_to_die))
		{
			log_level(&game->state.log_info, e_log_deaths,
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

int		advance_cycle(t_game_data *game)
{
	if (game->cycles_to_die <= 0 || !game->state.processes)
		return (0);
	vm_exec_cycle(&game->state);
	if (game->state.cycle_count - game->last_check >= (size_t)game->cycles_to_die)
	{
		kill_lazy_processes(game);
		game->last_check = game->state.cycle_count;
	}
	if (game->cycles_to_die <= 0 || !game->state.processes)
		return (0);
	return (1);
}
