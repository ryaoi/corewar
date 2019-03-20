/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_invert_bits.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:18:37 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/20 14:12:54 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	buffer_invert_bits(t_bigend_buffer buffer)
{
	size_t	index;

	index = 0;
	while (index < 8)
	{
		((uint8_t*)&buffer.buffer)[index] = ~(((uint8_t*)&buffer.buffer)[index]);
		index++;
	}
}
