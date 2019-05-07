/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:03:39 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/07 15:58:21 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static void	print_champions(t_vm_state *vm, t_game_data *game)
{
	size_t	i;

	i = 0;
	(void)game; /*TODO erase */
	while (i < vm->players.length)
	{
		wattron(win.info, COLOR_PAIR(50));
		mvwprintw(win.info, 14 + (i * 4), 3, "PLAYER -%d :", i + 1);
		wattron(win.info, COLOR_PAIR(3 + i));
		mvwprintw(win.info, 14 + (i * 4), 15, "%s",
			((t_player*)vm->players.ptr)[i].header.prog_name);
		wattron(win.info, COLOR_PAIR(50));
		mvwprintw(win.info, 15 + (i * 4), 3, "last_live_cycle : %zu",
			((t_player*)vm->players.ptr)[i].last_live_cycle);
		mvwprintw(win.info, 16 + (i * 4), 3, "nbr of 'live' execution : %zu",
			((t_player*)vm->players.ptr)[i].live);
		i++;
	}
}

static int	get_winner(t_game_data *game)
{
	size_t	winner;
	size_t	index;

	index = 1;
	winner = 0;
	while (index < game->state.players.length)
	{
		if (((t_player*)game->state.players.ptr)[index].live >
			((t_player*)game->state.players.ptr)[winner].live)
			winner = index;
		index++;
	}
	return (winner);
}

static void	draw_end(t_game_data *game)
{
	size_t	winner;
	size_t	champ_len;

	winner = get_winner(game);
	champ_len = ft_strlen(((t_player*)game->state.players.ptr)\
					[winner].header.prog_name);
	mvwprintw(win.info, 32, 3, "THE WINNER IS : ");
	wattron(win.info, COLOR_PAIR(3 + winner));
	mvwprintw(win.info, 32, 19, "%s",
	((t_player*)game->state.players.ptr)[winner].header.prog_name);
	wattron(win.info, COLOR_PAIR(50));
	mvwprintw(win.info, 32, 19 + champ_len, "!!!");
}

static void	output_info(t_vm_state *vm, t_game_data *game,
				t_input_info *input_info)
{
	wattron(win.info, COLOR_PAIR(50));
	if (input_info->pause == 0)
		mvwprintw(win.info, 2, 3, "** RUNNING **");
	else
		mvwprintw(win.info, 2, 3, "** PAUSE **");
	mvwprintw(win.info, 5, 3, "SPEED : %d Cycles/second", input_info->speed);
	mvwprintw(win.info, 7, 3, "CYCLE : %zu", vm->cycle_count);
	mvwprintw(win.info, 8, 3, "PROCCESSES : %d", vm->processes.length);
	mvwprintw(win.info, 10, 3, "CYCLE_TO_DIE : %d", game->cycles_to_die);
	print_champions(vm, game);
	if (vis_state.game_over)
		draw_end(game);
}

void	create_info(t_vm_state *vm, t_game_data *game,
			t_input_info *input_info)
{
	output_info(vm, game, input_info);
	wattron(win.info, COLOR_PAIR(1));
	box(win.info, '@', '@');
}
