/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champload.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:22:41 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/18 19:10:30 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <unistd.h>

int		main(void)
{
	t_vm_state	*state;

	if (!(state = malloc(sizeof(t_vm_state))))
		return (0);
	vm_state_init(state);
	if (vm_champion_load_file(state, "resources/test_champ1.cor") < 0
		|| vm_champion_load_file(state, "resources/test_champ2.cor") < 0)
		return (0);
	vm_memory_prepare(state);
	write(1, state->memory, MEM_SIZE);
}
