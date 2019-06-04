/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:10:25 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 23:14:58 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "handler_float.h"
#include <sys/types.h>

static void	flags_80(t_precise *precise, uint64_t mant, char sign)
{
	if (precise->exponent == -16383)
		precise->flags.exponent = EMPTY;
	else if (precise->exponent == 16384)
		precise->flags.exponent = FULL;
	else
		precise->flags.exponent = 0;
	if (mant & 0x3fffffffffffffff)
		precise->flags.mantissa = 1;
	else
		precise->flags.mantissa = 0;
	precise->flags.sign = sign;
}

int			float_80(long double num, t_precise *precise)
{
	uint64_t data[2];

	ft_memcpy(data, &num, sizeof(data));
	precise->exponent = (data[1] & 0x7fff) - 16383;
	flags_80(precise, data[0], (data[1] >> 15) & 1);
	if (precise->exponent == -16383)
		precise->exponent++;
	if (!(precise->mantissa = bi_init(2)))
		return (-1);
	precise->mantissa->data[0] = (uint32_t)data[0];
	precise->mantissa->data[1] = (uint32_t)(data[0] >> 32);
	if (precise->exponent - 63 > 0)
	{
		bi_bitshift_left(precise->mantissa, precise->exponent - 63);
		precise->exponent = 0;
	}
	else
		precise->exponent -= 63;
	precise->fractional = -precise->exponent;
	if (!precise->mantissa->size || scale_to_int(precise) < 0)
		return (-1);
	return (0);
}

static void	flags_64(t_precise *precise, uint64_t mant, char sign)
{
	if (precise->exponent == -1023)
		precise->flags.exponent = EMPTY;
	else if (precise->exponent == 1024)
		precise->flags.exponent = FULL;
	else
		precise->flags.exponent = 0;
	if (mant)
		precise->flags.mantissa = 1;
	else
		precise->flags.mantissa = 0;
	precise->flags.sign = sign;
}

int			float_64(double num, t_precise *precise)
{
	uint64_t	data;
	uint64_t	integral;

	ft_memcpy(&data, &num, sizeof(data));
	precise->exponent = ((data >> 52) & 0x7ff) - 1023;
	integral = data & 0x000fffffffffffff;
	flags_64(precise, integral, data >> 63);
	if (precise->exponent > -1023)
		integral |= 0x0010000000000000;
	else
		precise->exponent++;
	if (!(precise->mantissa = bi_init(2)))
		return (-1);
	precise->mantissa->data[0] = integral;
	precise->mantissa->data[1] = integral >> 32;
	if (precise->exponent - 52 > 0)
	{
		bi_bitshift_left(precise->mantissa, precise->exponent - 52);
		precise->exponent = 0;
	}
	else
		precise->exponent -= 52;
	precise->fractional = -precise->exponent;
	return ((!precise->mantissa->size || scale_to_int(precise) < 0) ? -1 : 0);
}
