/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_bitshift.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:53:27 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/10 13:20:09 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"
#include <stdlib.h>

void	bi_unitshift_right(t_bigint *num, size_t units)
{
	size_t	index;

	if (units > 0)
	{
		index = 0;
		while (index < num->size)
		{
			num->data[index] = (index + units < num->size) ?
				num->data[index + units] : 0;
			index++;
		}
	}
}

void	bi_bitshift_right(t_bigint *num, size_t bits)
{
	t_large	pad;
	t_unit	carry;
	size_t	whole_units;
	size_t	index;

	whole_units = bits / UNIT_BITS;
	bits -= whole_units * UNIT_BITS;
	bi_unitshift_right(num, whole_units);
	carry = 0;
	if (bits > 0)
	{
		index = num->size;
		while (index-- > 0)
		{
			pad = ((t_large)num->data[index] << UNIT_BITS) >> bits;
			num->data[index] = (t_unit)(pad >> UNIT_BITS) | carry;
			carry = (t_unit)pad;
		}
	}
	bi_cut(num);
}

void	bi_unitshift_left(t_bigint *num, size_t units)
{
	t_unit	*new_data;

	if (units > 0)
	{
		if (!(new_data = ft_memalloc(sizeof(t_unit) * (num->size + units))))
		{
			num->size = 0;
			return ;
		}
		ft_memcpy(new_data + units, num->data, sizeof(t_unit) * num->size);
		num->size += units;
		free(num->data);
		num->data = new_data;
	}
}

void	bi_bitshift_left(t_bigint *num, size_t bits)
{
	t_large	pad;
	t_unit	carry;
	size_t	whole_units;
	size_t	index;

	whole_units = bits / UNIT_BITS;
	bits -= whole_units * UNIT_BITS;
	bi_unitshift_left(num, whole_units);
	carry = 0;
	if (bits > 0)
	{
		index = 0;
		while (index < num->size)
		{
			pad = (t_large)num->data[index] << bits;
			num->data[index] = pad | carry;
			carry = (t_unit)(pad >> UNIT_BITS);
			index++;
		}
	}
	if (carry)
		bi_append(num, carry);
}
