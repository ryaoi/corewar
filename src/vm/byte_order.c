/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:03:24 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/20 14:12:59 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bigend_buffer	byte_order_swap(t_bigend_buffer input)
{
	t_bigend_buffer	output;
	size_t			index;

	index = 0;
	while (index < 8)
	{
		((uint8_t*)&output.buffer)[index] = ((uint8_t*)&input.buffer)[(8 - 1) - index];
		index++;
	}
	return (output);
}

