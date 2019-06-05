/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_dump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:03:26 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/05 14:02:41 by pmorgan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static int	get_champion_color(t_byte_info info, size_t cycle_count)
{
	int	color;

	if (info.written_player == -1)
		color = BLUE_BLACK;
	else if (info.written_player == -2)
		color = PURPLE_BLACK;
	else if (info.written_player == -3)
		color = GREEN_BLACK;
	else if (info.written_player == -4)
		color = RED_BLACK;
	else
		color = GREY_BLACK;
	if (cycle_count - info.written_cycle < HIGHLIGHT_CYCLE
		&& info.written_cycle > 1)
		color += HIGHLIGHT;
	if (info.pc_mark == 1)
		color += PROGRAM_COUNTER_MARK;
	return (color);
}

static void	output_memory_dump(t_vm_state *vm, t_visualizer_state *vis_state)
{
	size_t		index;
	size_t		col;
	size_t		row;
	int			color;
	t_window	win;

	index = 0;
	col = 0;
	row = 0;
	win = vis_state->win;
	while (index < MEM_SIZE)
	{
		color = get_champion_color(vm->memory_info[index], vm->cycle_count);
		wattron(win.mem_dump, COLOR_PAIR(color));
		mvwprintw(win.mem_dump, (2 + row), 3 + (col * 3),
			"%02X", vm->memory[index]);
		col++;
		index++;
		if (col == 64)
		{
			col = 0;
			row++;
		}
	}
	wattroff(win.info, COLOR_PAIR(color));
}

void		create_memory_dump(t_vm_state *vm, t_visualizer_state *vis_state)
{
	wattron(vis_state->win.mem_dump, COLOR_PAIR(1));
	box(vis_state->win.mem_dump, '@', '@');
	output_memory_dump(vm, vis_state);
	wattron(vis_state->win.mem_dump, COLOR_PAIR(1));
	box(vis_state->win.mem_dump, '@', '@');
}
