/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_mul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:54:26 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/10 13:21:04 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"

t_bigint	*bi_mul_small(const t_bigint *a, t_unit b)
{
	t_large		large;
	size_t		index;
	t_bigint	*product;

	product = bi_init(a->size + 1);
	if (!product)
		return (NULL);
	large = 0;
	index = 0;
	while (index < a->size)
	{
		large += (t_large)a->data[index] * b;
		product->data[index] = (t_unit)large;
		large = large >> (sizeof(t_unit) * 8);
		index++;
	}
	if (large)
		product->data[index] = (t_unit)large;
	if (!bi_cut(product))
	{
		free(product);
		return (NULL);
	}
	return (product);
}
