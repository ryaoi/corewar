/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:42:40 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/18 02:01:25 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void draw_mem_dump(t_window *win)
{
	size_t	index;
	size_t	col;
	size_t	row;

	index = 0;
	col = 0;
	row = 0;
	while (index < MEM_SIZE)
	{
		wattron(win->mem_dump, COLOR_PAIR(2));
		mvwprintw(win->mem_dump, (1 + row), 3 + (col * 3), "FF");
		col++;
		index++;
		if (col == 64)
		{
			col = 0;
			row++;
		}
	}
	wattroff(win->mem_dump, COLOR_PAIR(3));
}

void	create_memory_dump(t_window *win)
{
	wattron(win->mem_dump, COLOR_PAIR(1));
	box(win->mem_dump, '@', '@');
	draw_mem_dump(win);
	wattron(win->mem_dump, COLOR_PAIR(1));
	box(win->mem_dump, '@', '@');
}

void	visualize_game(t_window *win)
{
	werase(win->mem_dump);
//	werase(win->info);
	create_memory_dump(win);
//	create_info(win);
	refresh();
	wrefresh(win->mem_dump);
//	wrefresh(win->info);
}

void	get_color_pairs()
{
	init_color(COLOR_GREY, 350, 350, 350);
	init_color(COLOR_BRIGHT_WHITE, 1000, 1000, 1000);
	init_pair(1, COLOR_GREY, COLOR_GREY);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_GREY, COLOR_BLACK);
}

int		main()
{
	t_visualizer_state	vis_state;
	t_window			win;
	ft_bzero(&vis_state, sizeof(t_visualizer_state));
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	start_color();
	get_color_pairs();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	win.mem_dump = newwin(4 + (MEM_SIZE / 64), MEM_DUMP_WIDTH, 0, 0);
	win.info = newwin(4 + (MEM_SIZE / 64), INFO_WIDTH, 0, MEM_DUMP_WIDTH - 1);
	vis_state.speed = 100;
	vis_state.pause = 0;
	visualize_game(&win);
}
