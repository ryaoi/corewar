/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:55:19 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/15 17:21:17 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "game.h"
#include "ft_printf.h"

int		main(void)
{
	t_game_data	*game;
	t_array		players;
	t_player	sha1;
	t_player	sha2;
	t_log_info	info;

	if (vm_champion_load_file(&sha1, "/Users/aamadori/Downloads/vm_champs/champs/Gagnant.cor", -1) < 0
		|| vm_champion_load_file(&sha2, "/Users/aamadori/Downloads/vm_champs/champs/Octobre_Rouge_V4.2.cor", -2) < 0)
		return (0);
	array_init(&players, sizeof(t_player));
	array_push_back(&players, &sha1);
	array_push_back(&players, &sha2);
	logs_init(&info);
	info.log_mode = e_mode_stdout;
	ft_memcpy(&info.log_active,
		(uint8_t[e_log_level_max]){0, 1, 0, 0, 0, 0, 0, 1, 1, 0},
		sizeof(info.log_active));
	game = malloc(sizeof(t_game_data));
	prepare_game(game, &players, &info);
	while (advance_cycle(game))
		;
	dump_memory(&game->state);
	ft_printf("%d %d\n", ARRAY_PTR(game->state.players, t_player)[0].live, ARRAY_PTR(game->state.players, t_player)[1].live);
	return (0);
}
