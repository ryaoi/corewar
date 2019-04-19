/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:03:39 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/19 17:01:10 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"


static void	output_info(t_vm_state *vm)
{
	(void)vm;
	wattron(win.info, COLOR_PAIR(2));
	mvwprintw(win.info, 2, 3, "speed : %d cycles/second", vis_state.speed);
	mvwprintw(win.info, 3, 3, "cycle : %zu", vm->cycle_count);
	if (vis_state.pause == 0)
		mvwprintw(win.info, 4, 3, "-----fuck you alex!!-----");
	else
		mvwprintw(win.info, 4, 3, "-----go to hell alex!!!------");
}

void	create_info(t_vm_state *vm)
{
	wattron(win.info, COLOR_PAIR(1));
	box(win.info, '@', '@');
	output_info(vm);
	wattron(win.info, COLOR_PAIR(1));
	box(win.info, '@', '@');
}
