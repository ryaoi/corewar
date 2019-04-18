/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:03:39 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/18 12:10:29 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"


static void	output_info(t_window *win)
{
	wattron(win->info, COLOR_PAIR(2));
	for (int i=2; i < 64; i++)
		mvwprintw(win->info, i, 3, "fuuuuuk you aleexxx!!fuuuuuuk youu alllleleexx!!");

}

void	create_info(t_window *win)
{
	wattron(win->info, COLOR_PAIR(1));
	box(win->info, '@', '@');
	output_info(win);
	wattron(win->info, COLOR_PAIR(1));
	box(win->info, '@', '@');
}
