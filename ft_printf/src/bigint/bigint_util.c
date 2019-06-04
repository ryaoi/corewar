/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:44:55 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/10 14:09:21 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"
#include <stdlib.h>

t_bigint	*bi_init(size_t size)
{
	t_bigint	*ret;

	ret = ft_memalloc(sizeof(t_bigint));
	if (ret)
	{
		ret->data = ft_memalloc(sizeof(t_unit) * size);
		ret->size = size;
	}
	return (ret);
}

void		bi_destroy(t_bigint *num)
{
	if (num)
		free(num->data);
	free(num);
}

t_bigint	*bi_copy(t_bigint *src)
{
	t_bigint	*dest;

	dest = ft_memalloc(sizeof(t_bigint));
	if (dest)
	{
		dest->size = src->size;
		dest->data = ft_memalloc(sizeof(t_large) * dest->size);
	}
	return (dest);
}

size_t		bi_cut(t_bigint *num)
{
	t_unit	*new_data;
	ssize_t	index;

	index = num->size - 1;
	while (index >= 0 && !num->data[index])
		index--;
	if (index < 0)
		index = 0;
	if (index < (ssize_t)num->size - 1)
	{
		num->size = index + 1;
		if (!(new_data = malloc(sizeof(t_unit) * num->size)))
		{
			num->size = 0;
			free(num->data);
			return (0);
		}
		ft_memcpy(new_data, num->data, sizeof(t_unit) * num->size);
		free(num->data);
		num->data = new_data;
	}
	return (num->size);
}

size_t		bi_append(t_bigint *num, t_unit unit)
{
	t_unit	*new_data;

	if (!(new_data = malloc(sizeof(t_unit) * (num->size + 1))))
	{
		num->size = 0;
		free(num->data);
		return (0);
	}
	ft_memcpy(new_data, num->data, sizeof(t_unit) * num->size);
	new_data[num->size] = unit;
	free(num->data);
	num->size++;
	num->data = new_data;
	return (num->size);
}
