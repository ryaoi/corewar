/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:42:40 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/07 20:25:45 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include "visualizer.h"
#include "cmd_line.h"

static void	visualize_game(t_vm_state *vm, t_game_data *game,
			t_input_info *input_info)
{
	werase(win.mem_dump);
	werase(win.info);
	create_memory_dump(vm);
	create_info(vm, game, input_info);
	pthread_mutex_lock(&vis_state.input_lock);
	refresh();
	wnoutrefresh(win.mem_dump);
	wnoutrefresh(win.info);
	doupdate();
	pthread_mutex_unlock(&vis_state.input_lock);
}

static void	reset_ncurses(void)
{
	delwin(win.mem_dump);
	delwin(win.info);
	endwin();
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
}

int			visualizer(t_game_data *game, t_corewar_input *cw_input,
				t_input_info *info_copy)
{
	if (vis_state.game_over
		|| game->state.cycle_count >= cw_input->nbr_of_cycles)
		vis_state.game_over = 1;
	else if (!info_copy->pause)
	{
		if (advance_cycle(game) == 0)
			vis_state.game_over = 1;
	}
	if (info_copy->resize == 1)
	{
		reset_ncurses();
		return (0);
	}
	visualize_game(&game->state, game, info_copy);
	usleep(DELAY / info_copy->speed);
	return (0);
}
