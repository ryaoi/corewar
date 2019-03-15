/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:03:24 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/15 17:06:09 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_load_buffer	byte_order_swap(t_load_buffer input, size_t size)
{
	t_load_buffer	output;
	size_t			index;

	index = 0;
	while (index < size)
	{
		output.buffer[index] = input.buffer[(size - 1) - index];
		index++;
	}
	return (output);
}

