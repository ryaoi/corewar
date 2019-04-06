/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_invert_bits.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:18:37 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/06 19:15:54 by aamadori         ###   ########.fr       */
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
		INDEX_BUFF(output, index) = ~(INDEX_BUFF(input, index));
		index++;
	}
	return (output);
}
