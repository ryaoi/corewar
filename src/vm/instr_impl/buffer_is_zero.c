/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_is_zero.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:18:37 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/18 19:10:17 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

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
