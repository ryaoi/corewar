/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:55:19 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/21 15:43:53 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

int		main(void)
{
	t_vm_state	*state;
	t_array		players;
	t_player	sha1;
	t_player	sha2;
	size_t		index;
	size_t		line;

	if (vm_champion_load_file(&sha1, "resources/test_champ1.cor", 1) < 0
		|| vm_champion_load_file(&sha2, "resources/test_champ2.cor", 2) < 0)
		return (0);
	array_init(&players, sizeof(t_player));
	array_push_back(&players, &sha1);
	array_push_back(&players, &sha2);
	play_game(&players, &state, 10000);
	line = 0;
	while (line < 64)
	{
		index = 0;
		while(index < 64)
		{
			ft_printf("%2.2hhx ", state->memory[(line * 64) + index]);
			index++;
		}
		ft_printf("\n");
		line++;
	}
	ft_printf("\n");
	ft_printf("%d %d\n", ARRAY_PTR(state->players, t_player)[0].live, ARRAY_PTR(state->players, t_player)[1].live);
}
