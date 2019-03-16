/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:03:24 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/15 19:42:48 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bigend_buffer	byte_order_swap(t_bigend_buffer input, size_t size)
{
	t_bigend_buffer	output;
	size_t			index;

	index = 0;
	while (index < size)
	{
		output.buffer[index] = input.buffer[(size - 1) - index];
		index++;
	}
	return (output);
}
