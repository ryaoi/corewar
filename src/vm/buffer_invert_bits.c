/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_invert_bits.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:18:37 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/01 17:03:32 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bigend_buffer	buffer_invert_bits(t_bigend_buffer input)
{
	t_bigend_buffer	output;
	size_t			index;

	index = 0;
	while (index < sizeof(output.buffer))
	{
		((uint8_t*)&output.buffer)[index] = ~(((uint8_t*)&input.buffer)[index]);
		index++;
	}
	return (output);
}
