/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 16:07:19 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/21 19:05:09 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	close_ncurses(t_visualizer_state *vis_state)
{
	nodelay(stdscr, FALSE);
	wattron(vis_state->win.info, COLOR_PAIR(50));
	mvwprintw(vis_state->win.info, 28, 3, "** PRESS ANY KEY TO EXIT **");
	wrefresh(vis_state->win.info);
	getch();
	delwin(vis_state->win.mem_dump);
	delwin(vis_state->win.info);
	endwin();
}

void	init_visualizer(t_visualizer_state *vis_state)
{
	ft_bzero(vis_state, sizeof(t_visualizer_state));
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	start_color();
	get_colors();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	vis_state->win.mem_dump = newwin(4 + (MEM_SIZE / 64), MEM_DUMP_WIDTH, 0, 0);
	vis_state->win.info =
		newwin(4 + (MEM_SIZE / 64), INFO_WIDTH, 0, MEM_DUMP_WIDTH - 1);
	ft_bzero(&vis_state->input_info, sizeof(vis_state->input_info));
	vis_state->input_info.speed = 500;
	vis_state->input_info.pause = 1;
	vis_state->shutdown = 0;
	vis_state->game_over = 0;
	pthread_create(&vis_state->input_worker, NULL,
		input_loop_wrapper, vis_state);
	pthread_mutex_init(&vis_state->input_lock, NULL);
}
