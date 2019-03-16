/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_is_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:18:37 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/16 15:20:53 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

int		buffer_is_zero(t_bigend_buffer buffer, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		if (buffer.buffer)
			return (0);
		index++;
	}
	return (1);
}
