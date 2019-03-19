/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champload.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:22:41 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/19 19:43:42 by aamadori         ###   ########.fr       */
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
	index = 0;
	while (index < MEM_SIZE)
		ft_printf("%2.2hhx ", state->memory[index++]);
	ft_printf("\n");
}
