/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_sum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:16:41 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/10 13:24:00 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"

t_bigint	*bi_sum_small(const t_bigint *a, t_unit s)
{
	t_large		large;
	size_t		index;
	t_bigint	*ret;

	ret = bi_init(a->size);
	if (!ret)
		return (NULL);
	large = 0;
	index = 0;
	while (index < a->size)
	{
		large += a->data[index];
		if (index == 0)
			large += s;
		ret->data[index] = (t_unit)large;
		large = large >> (sizeof(t_unit) * 8);
		index++;
	}
	if (large && !bi_append(ret, large))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

t_bigint	*bi_sum(const t_bigint *a, const t_bigint *b, size_t max_len)
{
	t_large		large;
	size_t		index;
	t_bigint	*ret;

	ret = bi_init(ft_max(a->size, b->size));
	large = 0;
	index = 0;
	while (index < (size_t)ft_max(a->size, b->size))
	{
		if (index < a->size)
			large += a->data[index];
		if (index < b->size)
			large += b->data[index];
		ret->data[index] = (t_unit)large;
		large = large >> (sizeof(t_unit) * 8);
		index++;
	}
	if (large && (!max_len || ret->size < max_len) && !bi_append(ret, large))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

t_bigint	*bi_complement(const t_bigint *a, size_t size)
{
	t_large		large;
	size_t		index;
	t_bigint	*ret;

	ret = bi_init(size);
	if (!ret)
		return (NULL);
	index = 0;
	large = 1;
	while (index < size)
	{
		if (index < a->size)
			large += (t_large)(~a->data[index]);
		else
			large += (t_large)(~((t_unit)0));
		ret->data[index] = large;
		large = large >> (sizeof(t_unit) * 8);
		index++;
	}
	return (ret);
}

t_bigint	*bi_difference(const t_bigint *a, const t_bigint *b)
{
	t_bigint *complement;
	t_bigint *ret;

	complement = NULL;
	ret = NULL;
	if (!(complement = bi_complement(b, a->size))
		|| !(ret = bi_sum(a, complement, a->size)))
	{
		free(complement);
		free(ret);
		return (NULL);
	}
	bi_destroy(complement);
	if (!bi_cut(ret))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
