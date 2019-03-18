/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_store.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:19:53 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/18 21:03:45 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/* TODO always load and store memory through these functions */
/* TODO compile-time ASSERT if REG_SIZE is too big */
t_bigend_buffer	mem_load(t_vm_state *state, size_t address, size_t size)
{
	t_bigend_buffer	ret;
	size_t			byte_address;
	size_t			index;

	/* TODO assert size is not larger than REG_SIZE */
	index = 0;
	while (index < size)
	{
		byte_address = (address + index) % MEM_SIZE;
		((uint8_t*)&ret.buffer)[index] = state->memory[byte_address];
		index++;
	}
	return	ret;
}

void	mem_store(t_vm_state *state, size_t address, size_t size,
			const t_bigend_buffer store)
{
	size_t			byte_address;
	size_t			index;

	/* TODO assert size is not larger than REG_SIZE */
	index = 0;
	while (index < size)
	{
		byte_address = (address + index) % MEM_SIZE;
		state->memory[byte_address] = ((const uint8_t*)&store.buffer)[index];
		index++;
	}
}
