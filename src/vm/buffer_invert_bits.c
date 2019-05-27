/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_invert_bits.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:18:37 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 18:24:04 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_bigend_buffer	buffer_invert_bits(t_bigend_buffer input)
{
	t_bigend_buffer	output;
	size_t			index;

	index = 0;
	ft_bzero(&output, sizeof(t_bigend_buffer));
	while (index < sizeof(output.buffer))
	{
		(*(buff_index(&output, index))) = ~(*(buff_index(&input, index)));
		index++;
	}
	return (output);
}
