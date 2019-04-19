/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:03:26 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/19 19:34:31 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static int	get_champion_color(size_t index, t_byte_info info, size_t cycle_count)
{
	int	color;

	(void)cycle_count;
	(void)index;
	if (info.written_player == -1)
		color = 3;
	else if (info.written_player == -2)
		color = 4;
	else if (info.written_player == -3)
		color = 5;
	else if (info.written_player == -4)
		color = 6;

	else
		color = 2;
	/* TODO highlight */
	return (color);
}

static void output_memory_dump(t_vm_state *vm)
{
	size_t	index;
	size_t	col;
	size_t	row;
	int		color;

	index = 0;
	col = 0;
	row = 0;
	while (index < MEM_SIZE)
	{
		color = get_champion_color(index, vm->memory_info[index], vm->cycle_count);
		wattron(win.mem_dump, COLOR_PAIR(color));
		mvwprintw(win.mem_dump, (2 + row), 3 + (col * 3), "%02X", vm->memory[index]);
		col++;
		index++;
		if (col == 64)
		{
			col = 0;
			row++;
		}
	}
	wattroff(win.info, COLOR_PAIR(1));
}

void		create_memory_dump(t_vm_state *vm)
{
	wattron(win.mem_dump, COLOR_PAIR(1));
	box(win.mem_dump, '@', '@');
	output_memory_dump(vm);
	wattron(win.mem_dump, COLOR_PAIR(1));
	box(win.mem_dump, '@', '@');
}
