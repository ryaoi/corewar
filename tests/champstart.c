/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champstart.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:22:41 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/19 19:42:48 by aamadori         ###   ########.fr       */
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
	if (vm_champion_load_file(state, "resources/test_champ2.cor", 1) < 0)
		return (0);
	vm_memory_prepare(state);
	vm_init_process(state, 1);
	index = 0;
	while (index < 10)
	{
		vm_exec_cycle(state);
		index++;
	}
	ft_printf("%d\n", ARRAY_PTR(state->players, t_player)[0].live);
}
