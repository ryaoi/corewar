/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 19:55:19 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/19 21:28:30 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

int		main(void)
{
	t_vm_state	*state;
	size_t		index;

	if (!(state = malloc(sizeof(t_vm_state))))
		return (0);
	vm_state_init(state);
	if (vm_champion_load_file(state, "resources/test_champ1.cor", 1) < 0
		|| vm_champion_load_file(state, "resources/test_champ2.cor", 2) < 0)
		return (0);
	vm_memory_prepare(state);
	vm_init_process(state, 0, 0);
	vm_init_process(state, 1, MEM_SIZE / state->players.length);
	index = 0;
	while (index < 4000)
	{
		/* TODO kill some processes or it multiplies too much, I guess? */
		vm_exec_cycle(state);
		index++;
	}
	index = 0;
	while (index < MEM_SIZE)
		ft_printf("%2.2hhx ", state->memory[index++]);
	ft_printf("\n");
	ft_printf("%d %d\n", ARRAY_PTR(state->players, t_player)[0].live, ARRAY_PTR(state->players, t_player)[1].live);
}
