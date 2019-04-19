/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:03:26 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/18 22:23:05 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void output_memory_dump(t_vm_state *vm)
{
	size_t	index;
	size_t	col;
	size_t	row;

	index = 0;
	col = 0;
	row = 0;
	while (index < MEM_SIZE)
	{
		wattron(win.mem_dump, COLOR_PAIR(2));
		mvwprintw(win.mem_dump, (2 + row), 3 + (col * 3), "%02X", vm->memory[index]);
		col++;
		index++;
		if (col == 64)
		{
			col = 0;
			row++;
		}
	}
}

void		create_memory_dump(t_vm_state *vm)
{
	wattron(win.mem_dump, COLOR_PAIR(1));
	box(win.mem_dump, '@', '@');
	output_memory_dump(vm);
	wattron(win.mem_dump, COLOR_PAIR(1));
	box(win.mem_dump, '@', '@');
}
