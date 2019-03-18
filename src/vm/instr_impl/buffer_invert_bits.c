/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_invert_bits.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:18:37 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/18 21:14:23 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	buffer_invert_bits(t_bigend_buffer buffer, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		((uint8_t*)&buffer.buffer)[index] = ~(((uint8_t*)&buffer.buffer)[index]);
		index++;
	}
}
