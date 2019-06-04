/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_div.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 15:13:33 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/10 13:21:47 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"

t_bigint	*bi_div_small(const t_bigint *num, t_unit div, t_unit *mod_ret)
{
	t_bigint	*quotient;
	size_t		l_index;
	t_large		large;
	t_unit		mod;

	quotient = bi_init(num->size);
	if (!quotient)
		return (NULL);
	mod = 0;
	l_index = num->size;
	while (l_index > 0)
	{
		l_index--;
		large = ((t_large)mod << UNIT_BITS) | num->data[l_index];
		mod = (t_unit)(large % div);
		quotient->data[l_index] = (t_unit)(large / div);
	}
	if (!bi_cut(quotient))
	{
		free(quotient);
		return (NULL);
	}
	if (mod_ret)
		*mod_ret = mod;
	return (quotient);
}
