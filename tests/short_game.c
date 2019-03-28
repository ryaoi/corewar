/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:55:19 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/28 15:02:56 by aamadori         ###   ########.fr       */
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

	if (vm_champion_load_file(&sha1, "resources/test_champ1.cor", 1) < 0
		|| vm_champion_load_file(&sha2, "resources/test_champ2.cor", 2) < 0)
		return (0);
	array_init(&players, sizeof(t_player));
	array_push_back(&players, &sha1);
	array_push_back(&players, &sha2);
	logs_init(&info);
	info.log_mode = e_mode_save;
	game = malloc(sizeof(t_game_data));
	prepare_game(game, &players, &info);
	while (advance_cycle(game) && game->state.cycle_count < 10000)
		;
	dump_memory(&game->state);
	ft_printf("%d %d\n", ARRAY_PTR(game->state.players, t_player)[0].live, ARRAY_PTR(game->state.players, t_player)[1].live);
}
