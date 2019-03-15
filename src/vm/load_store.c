/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_store.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:19:53 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/15 15:33:23 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* TODO always load and store memory through these functions */
/* TODO compile-time ASSERT if REG_SIZE is too big */
t_load_buffer	mem_load(t_vm_state *state, size_t address, size_t size)
{
	t_load_buffer	ret;
	size_t			byte_address;
	size_t			index;

	/* TODO assert size is not larger than REG_SIZE */
	index = 0;
	while (index < size)
	{
		byte_address = (address + index) % MEM_SIZE;
		ret.buffer[index] = state->memory[byte_address];
		index++;
	}
	return	ret;
}

void	mem_store(t_vm_state *state, size_t address, size_t size,
			const t_load_buffer store)
{
	size_t			byte_address;
	size_t			index;

	/* TODO assert size is not larger than REG_SIZE */
	index = 0;
	while (index < size)
	{
		byte_address = (address + index) % MEM_SIZE;
		state->memory[byte_address] = store.buffer[index];
		index++;
	}
}
