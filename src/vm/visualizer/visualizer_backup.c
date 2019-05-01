/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_backup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:55:19 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/01 18:40:11 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "game.h"
#include "ft_printf.h"
#include "cmd_line.h"
#include "visualizer.h"

void	*input_loop(void *stub)
{
	int key;

	(void)stub;
	while (!vis_state.shutdown)
	{
		pthread_mutex_lock(&vis_state.input_lock);
		key = 1;
		while (key)
			key = get_keyinput(&vis_state);
		pthread_mutex_unlock(&vis_state.input_lock);
		usleep(10000);
	}
	return (NULL);
}

void	init_visualizer(void)
{
	ft_bzero(&vis_state, sizeof(t_visualizer_state));
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	start_color();
	get_colors();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	win.mem_dump = newwin(4 + (MEM_SIZE / 64), MEM_DUMP_WIDTH, 0, 0);
	win.info = newwin(4 + (MEM_SIZE / 64), INFO_WIDTH, 0, MEM_DUMP_WIDTH - 1);
	ft_bzero(&vis_state.input_info, sizeof(vis_state.input_info));
	vis_state.input_info.speed = 1000;
	vis_state.input_info.pause = 1;
	vis_state.shutdown = 0;
	vis_state.game_over = 0;
	pthread_create(&vis_state.input_worker, NULL, input_loop, NULL);
	pthread_mutex_init(&vis_state.input_lock, NULL);
}

void	start_game(t_game_data *game, t_corewar_input *cw_input)
{
	t_input_info	info_copy;

	if (cw_input->exec_flags & FLAG_VISUALIZER)
	{
		init_visualizer();
		info_copy.quit = 0;
		while (!info_copy.quit)
		{
			pthread_mutex_lock(&vis_state.input_lock);
			ft_memcpy(&info_copy, &vis_state.input_info, sizeof(info_copy));
			pthread_mutex_unlock(&vis_state.input_lock);
			visualizer(game, cw_input, &info_copy);
		}
		vis_state.shutdown = 1;
		pthread_join(vis_state.input_worker, NULL);
		delwin(win.mem_dump);
		delwin(win.info);
		endwin();
	}
	else
	{
		while (game->state.cycle_count < cw_input->nbr_of_cycles)
			if (advance_cycle(game) == 0)
				break ;
	}
	if (cw_input->exec_flags & FLAG_MEMDUMP)
		dump_memory(&game->state);
}

void	initialize_logging(t_log_info *info, t_corewar_input *cw_input)
{
	if (cw_input->exec_flags & FLAG_VISUALIZER)
		ft_bzero(cw_input->log_verbosity, e_log_level_max);
	logs_init(info);
	ft_memcpy(info->log_active,
		cw_input->log_verbosity, sizeof(info->log_active));
}

int	load_champions(t_corewar_input *cw_input, t_array *players)
{
	t_player	player;
	int			index;

	array_init(players, sizeof(t_player));
	index = 0;
	while (index < MAX_CHAMP_NBR)
	{
		if (cw_input->champions[index] != NULL)
		{
			ft_printf("champ[%d] : %s\n", index + 1, cw_input->champions[index]);
			if (vm_champion_load_file(&player, cw_input->champions[index], -(index + 1)) < 0)
				return (FT_FAIL);
			array_push_back(players, &player);
		}
		index++;
	}
	return (FT_SUCCESS);
}

int main(int argc, char **argv)
{
	t_corewar_input	corewar_input;
	t_game_data		*game;
	t_array			players;
	t_log_info		info;
	int				ret;

	ret = parse_cmd(argc, argv, &corewar_input);
	if (ret == FT_SUCCESS)
		ret = load_champions(&corewar_input, &players);
	if (ret == FT_SUCCESS)
	{
		initialize_logging(&info, &corewar_input);
		game = malloc(sizeof(t_game_data));
		prepare_game(game, &players, &info);
		start_game(game, &corewar_input);
	}
	return (0);
}

/*
int		main(void)
{
	t_game_data	*game;
	t_array		players;
	t_player	sha1;
	t_player	sha2;
	t_player	sha3;
	t_player	sha4;
	t_log_info	info;

	if (vm_champion_load_file(&sha1, "/Users/jaelee/42/corewar/champs/Gagnant.cor", -1) < 0
		|| vm_champion_load_file(&sha2, "/Users/jaelee/42/corewar/champs/Octobre_Rouge_V4.2.cor", -2) < 0
		|| vm_champion_load_file(&sha3, "/Users/jaelee/42/corewar/death.cor", -3) < 0
		|| vm_champion_load_file(&sha4, "/Users/jaelee/42/corewar/champs/fluttershy.cor", -4) < 0)
		return (0);
	array_init(&players, sizeof(t_player));
	array_push_back(&players, &sha1);
	array_push_back(&players, &sha2);
	array_push_back(&players, &sha3);
	array_push_back(&players, &sha4);
	logs_init(&info);
	info.log_mode = e_mode_stderr;
	ft_memcpy(&info.log_active,
		(uint8_t[e_log_level_max]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		sizeof(info.log_active));
	game = malloc(sizeof(t_game_data));
	prepare_game(game, &players, &info);
	while (game->state.cycle_count < 80000)
	{
		advance_cycle(game);
	//	dump_memory(&game->state);
		if (visualizer(game) == -1)
			break ;
	}
	close_ncurse(&win);
//	ft_printf("%d %d\n", ARRAY_PTR(game->state.players, t_player)[0].live, ARRAY_PTR(game->state.players, t_player)[1].live);
	return (0);
}
*/
