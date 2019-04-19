/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:03:39 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/18 22:56:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"


static void	output_info(t_vm_state *vm)
{
	(void)vm;
	wattron(win.info, COLOR_PAIR(2));
	mvwprintw(win.info, 2, 3, "speed : %d", vis_state.speed);
	mvwprintw(win.info, 3, 3, "cycle : %zu", vm->cycle_count);
	if (vis_state.pause == 0)
		mvwprintw(win.info, 4, 3, "----running!!-----");
	else
		mvwprintw(win.info, 4, 3, "-----paused!!!------");
	mvwprintw(win.info, 5, 3, "delwin(win.mem_dump) addr : %p\n", win.mem_dump);
	mvwprintw(win.info, 6, 3, "delwin(win.info) addr : %p\n", win.info);
}

void	create_info(t_vm_state *vm)
{
	wattron(win.info, COLOR_PAIR(1));
	box(win.info, '@', '@');
	output_info(vm);
	wattron(win.info, COLOR_PAIR(1));
	box(win.info, '@', '@');
}
