/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:07:19 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/07 19:36:37 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	close_ncurses(void)
{
	nodelay(stdscr, FALSE);
	wattron(win.info, COLOR_PAIR(50));
	mvwprintw(win.info, 28, 3, "** PRESS ANY KEY TO EXIT **");
	wrefresh(win.info);
	getch();
	delwin(win.mem_dump);
	delwin(win.info);
	endwin();
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
	vis_state.input_info.speed = 500;
	vis_state.input_info.pause = 1;
	vis_state.shutdown = 0;
	vis_state.game_over = 0;
	pthread_create(&vis_state.input_worker, NULL, input_loop, NULL);
	pthread_mutex_init(&vis_state.input_lock, NULL);
}
