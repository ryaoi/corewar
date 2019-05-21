/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:42:40 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/21 16:58:10 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include "visualizer.h"
#include "cmd_line.h"

static void	visualize_game(t_vm_state *vm, t_game_data *game,
			t_input_info *input_info, t_window *win)
{
	werase(win->mem_dump);
	werase(win->info);
	create_memory_dump(vm, win);
	create_info(vm, game, input_info, win);
	pthread_mutex_lock(&g_vis_state.input_lock);
	refresh();
	wnoutrefresh(win->mem_dump);
	wnoutrefresh(win->info);
	doupdate();
	pthread_mutex_unlock(&g_vis_state.input_lock);
}

static void	reset_ncurses(t_window *win)
{
	delwin(win->mem_dump);
	delwin(win->info);
	endwin();
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	start_color();
	get_colors();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	win->mem_dump = newwin(4 + (MEM_SIZE / 64), MEM_DUMP_WIDTH, 0, 0);
	win->info = newwin(4 + (MEM_SIZE / 64), INFO_WIDTH, 0, MEM_DUMP_WIDTH - 1);
}

int			visualizer(t_game_data *game, t_corewar_input *cw_input,
				t_input_info *info_copy, t_window *win)
{
	if (g_vis_state.game_over
		|| game->state.cycle_count >= cw_input->nbr_of_cycles)
		g_vis_state.game_over = 1;
	else if (!info_copy->pause)
	{
		if (advance_cycle(game) == 0)
			g_vis_state.game_over = 1;
	}
	if (info_copy->resize == 1)
	{
		reset_ncurses(win);
		return (0);
	}
	visualize_game(&game->state, game, info_copy, win);
	usleep(DELAY / info_copy->speed);
	return (0);
}
