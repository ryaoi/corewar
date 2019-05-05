/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:42:40 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/05 17:33:09 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include "visualizer.h"
#include "cmd_line.h"

void	visualize_game(t_vm_state *vm, t_game_data *game,
			t_input_info *input_info)
{
	werase(win.mem_dump);
	werase(win.info);
	create_memory_dump(vm);
	create_info(vm, game, input_info);
	refresh();
	wnoutrefresh(win.mem_dump);
	wnoutrefresh(win.info);
	doupdate();
}

int		visualizer(t_game_data *game, t_corewar_input *cw_input)//,t_input_info *info_copy)
{
	if (vis_state.game_over
		|| game->state.cycle_count >= cw_input->nbr_of_cycles)
		vis_state.game_over = 1;
		/* print quit message if game_over */
//	else if (!info_copy->pause)
	else if (vis_state.input_info.pause == 1)
	{
		if (advance_cycle(game) == 0)
			vis_state.game_over = 1;
	//	usleep(DELAY / info_copy->speed);
		usleep(DELAY / vis_state.input_info.speed);
	}
	//if (info_copy->resize == 1)
	if (vis_state.input_info.resize == 1)
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
		vis_state.input_info.resize = 0;
		return (0);
	}
	visualize_game(&game->state, game, &vis_state.input_info);
	return (0);
}
