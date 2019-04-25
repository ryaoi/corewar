/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:42:40 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/25 18:22:13 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	visualize_game(t_vm_state *vm, t_game_data *game)
{
	vis_state.delay = DELAY / vis_state.speed;
	werase(win.mem_dump);
	werase(win.info);
	create_memory_dump(vm);
	create_info(vm, game);
	refresh();
	wrefresh(win.mem_dump);
	wrefresh(win.info);
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
	vis_state.speed = 1000;
	vis_state.pause = 1;
}

int		visualizer(t_game_data *game)
{
	int					key;

	if (game->state.cycle_count == 1)
		init_visualizer();
	while (vis_state.pause)
	{
		key = get_keyinput(&vis_state);
		visualize_game(&game->state, game);
		if (key == -1)
			return (-1);
		else if (key == 1)
			return (0);
	}
	visualize_game(&game->state, game);
	if (get_keyinput(&vis_state) == -1)
		return (-1);
	usleep(vis_state.delay);
	return (0);
}
