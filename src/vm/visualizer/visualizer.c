/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 23:42:40 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/30 18:01:40 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <curses.h>
#include "visualizer.h"
#include "cmd_line.h"

void	visualize_game(t_vm_state *vm, t_game_data *game,
			t_input_info *input_info)
{
	werase(win.mem_dump);
	werase(win.info);
	create_memory_dump(vm);
	create_info(vm, game, input_info);
	refresh();
	wrefresh(win.mem_dump);
	wrefresh(win.info);
}

int		visualizer(t_game_data *game, t_corewar_input *cw_input,
			t_input_info *info_copy)
{
	if (vis_state.game_over
		|| game->state.cycle_count >= cw_input->nbr_of_cycles)
		vis_state.game_over = 1;
		/* print quit message if game_over */
	else if (!info_copy->pause)
	{
		if (advance_cycle(game) == 0)
			vis_state.game_over = 1;
	}
	visualize_game(&game->state, game, info_copy);
	usleep(DELAY / info_copy->speed);
	return (0);
}
