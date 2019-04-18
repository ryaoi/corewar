/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:03:26 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/18 12:10:22 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void output_memory_dump(t_window *win)
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
		if (col % 2 == 0)
			mvwprintw(win->mem_dump, (2 + row), 3 + (col * 3), "00");
		else
			mvwprintw(win->mem_dump, (2 + row), 3 + (col * 3), "FF");
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

void		create_memory_dump(t_window *win)
{
	wattron(win->mem_dump, COLOR_PAIR(1));
	box(win->mem_dump, '@', '@');
	output_memory_dump(win);
	wattron(win->mem_dump, COLOR_PAIR(1));
	box(win->mem_dump, '@', '@');
}
