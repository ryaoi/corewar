/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_store.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:19:53 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 18:23:17 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_assert.h"

t_bigend_buffer	mem_load(t_vm_state *state, int64_t address, size_t size)
{
	t_bigend_buffer	ret;
	size_t			byte_address;
	size_t			msb;
	size_t			index;

	ASSERT(size <= REG_SIZE, "Tried to load size larger than REG_SIZE");
	index = 0;
	ret.buffer = 0;
	msb = sizeof(ret.buffer) - size;
	while (index < size)
	{
		byte_address = (address + index) % MEM_SIZE;
		((uint8_t*)&ret.buffer)[index + msb] = state->memory[byte_address];
		index++;
	}
	index = 0;
	while ((*(buff_index(&ret, msb)) & 0x80) && index < msb)
	{
		*(buff_index(&ret, index)) = 0xff;
		index++;
	}
	return (ret);
}

void			mem_store(t_vm_state *state, int64_t address, size_t size,
					const t_bigend_buffer store)
{
	size_t			byte_address;
	size_t			index;
	size_t			msb;
	int				player_id;

	ASSERT(size <= REG_SIZE, "Tried to store size larger than REG_SIZE");
	index = 0;
	msb = sizeof(store.buffer) - size;
	while (index < size)
	{
		byte_address = (address + index) % MEM_SIZE;
		player_id = state->current_process->player->id;
		state->memory_info[byte_address].written_player = player_id;
		state->memory_info[byte_address].written_cycle = state->cycle_count;
		state->memory[byte_address] = (
			(const uint8_t*)&store.buffer)[index + msb];
		index++;
	}
}
