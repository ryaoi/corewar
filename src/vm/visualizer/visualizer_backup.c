/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer_backup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:55:19 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/19 16:11:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "game.h"
#include "ft_printf.h"
#include "visualizer.h"

void	close_ncurse(t_window *win)
{
	nodelay(stdscr, FALSE);
	getch();
	(void)win;
	printf("\ndelwin(mem_dump) returns : %d\n", delwin((*win).mem_dump));
	printf("\ndelwin() returns : %d\n", delwin((*win).info));
	printf("\nendwin returns : %d\n", endwin());
}

int		main(void)
{
	t_game_data	*game;
	t_array		players;
	t_player	sha1;
	t_player	sha2;
	t_log_info	info;

	if (vm_champion_load_file(&sha1, "/Users/jaelee/42/corewar/champs/Gagnant.cor", -1) < 0
		|| vm_champion_load_file(&sha2, "/Users/jaelee/42/corewar/champs/Octobre_Rouge_V4.2.cor", -2) < 0)
		return (0);
	array_init(&players, sizeof(t_player));
	array_push_back(&players, &sha1);
	array_push_back(&players, &sha2);
	logs_init(&info);
	info.log_mode = e_mode_stderr;
	ft_memcpy(&info.log_active,
		(uint8_t[e_log_level_max]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		sizeof(info.log_active));
	game = malloc(sizeof(t_game_data));
	prepare_game(game, &players, &info);
	while (game->state.cycle_count < 14973)
	{
		advance_cycle(game);
	//	dump_memory(&game->state);
		if (visualizer(game) == -1)
			break ;
	}
	printf("\naddr of win.memdump at end : %p\n", win.mem_dump);
	printf("\naddr of win.info at end : %p\n", win.info);
	close_ncurse(&win);
//	ft_printf("%d %d\n", ARRAY_PTR(game->state.players, t_player)[0].live, ARRAY_PTR(game->state.players, t_player)[1].live);
	return (0);
}
