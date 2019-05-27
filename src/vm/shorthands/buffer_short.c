/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_short.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:18:11 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 18:22:02 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint8_t		*buff_index(t_bigend_buffer *buffer, size_t id)
{
	return ((uint8_t*)&buffer->buffer + id);
}
