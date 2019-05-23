/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:55:19 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/23 16:56:42 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "game.h"
#include "cmd_line.h"
#include "visualizer.h"
#include "ft_assert.h"

static void	play_game(t_game_data *game, t_corewar_input *cw_input)
{
	while (game->state.cycle_count < cw_input->nbr_of_cycles)
	{
		if (advance_cycle(game) == 0)
		{
			print_ending(&game->state);
			break ;
		}
	}
}

void		start_game(t_game_data *game, t_corewar_input *cw_input)
{
	t_input_info		info_copy;
	t_visualizer_state	vis_state;

	if (cw_input->exec_flags & FLAG_VISUALIZER)
	{
		init_visualizer(&vis_state);
		info_copy.quit = 0;
		while (!vis_state.input_info.quit)
		{
			pthread_mutex_lock(&vis_state.input_lock);
			ft_memcpy(&info_copy, &vis_state.input_info, sizeof(info_copy));
			vis_state.input_info.resize = 0;
			pthread_mutex_unlock(&vis_state.input_lock);
			visualizer(game, cw_input, &info_copy, &vis_state);
		}
		vis_state.shutdown = 1;
		pthread_join(vis_state.input_worker, NULL);
		close_ncurses(&vis_state);
	}
	else
		play_game(game, cw_input);
	if (cw_input->exec_flags & FLAG_MEMDUMP)
		dump_memory(&game->state);
}

void		initialize_logging(t_log_info *info, t_corewar_input *cw_input)
{
	if (cw_input->exec_flags & FLAG_VISUALIZER)
		ft_bzero(cw_input->log_verbosity, e_log_level_max);
	logs_init(info);
	ft_memcpy(info->log_active,
		cw_input->log_verbosity, sizeof(info->log_active));
}

int			load_champions(t_corewar_input *cw_input, t_array *players)
{
	t_player	player;
	int			index;

	if (cw_input->nbr_of_champions < 1)
	{
		print_usage();
		return (FT_FAIL);
	}
	array_init(players, sizeof(t_player));
	index = 0;
	while (index < MAX_CHAMP_NBR)
	{
		if (cw_input->champions[index] != NULL)
		{
			if (vm_champion_load_file(&player, cw_input->champions[index],
										-(index + 1)) < 0)
				return (FT_FAIL);
			array_push_back(players, &player);
		}
		index++;
	}
	return (FT_SUCCESS);
}

int			main(int argc, char **argv)
{
	t_corewar_input	corewar_input;
	t_game_data		*game;
	t_array			players;
	t_log_info		info;

	if (parse_cmd(argc, argv, &corewar_input) == FT_SUCCESS)
	{
		array_init(&players, sizeof(t_player));
		if (load_champions(&corewar_input, &players))
		{
			initialize_logging(&info, &corewar_input);
			game = malloc(sizeof(t_game_data));
			/* TODO call this everytime you malloc */
			MALLOC_ASSERT(game);
			prepare_game(game, &players, &info);
			print_prelude(&game->state);
			start_game(game, &corewar_input);
			vm_state_clear(&game->state);
			free(game);
			game = NULL;
		}
		array_clear(&players, NULL);
	}
	free_input(&corewar_input);
	return (0);
}
