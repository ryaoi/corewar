/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_order.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:03:24 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 18:22:36 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bigend_buffer	byte_order_swap(t_bigend_buffer input)
{
	t_bigend_buffer	output;
	size_t			index;

	index = 0;
	ft_bzero(&output, sizeof(t_bigend_buffer));
	while (index < sizeof(input.buffer))
	{
		*(buff_index(&output, index)) = ((uint8_t*)&input.buffer)
			[(sizeof(input.buffer) - 1) - index];
		index++;
	}
	return (output);
}
