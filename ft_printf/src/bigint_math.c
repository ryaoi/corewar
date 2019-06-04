/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bigint_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 00:51:42 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/13 16:46:42 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bigint.h"
#include "handler_float.h"
#include "ft_printf.h"
#include <stdlib.h>

static void		round_to_even(t_precise *prec, ssize_t cut)
{
	t_bigint	*swap;
	uint32_t	last_digit;
	char		just_zeroes;
	ssize_t		index;

	last_digit = 0;
	index = 0;
	just_zeroes = 1;
	while (index < cut)
	{
		prec->fractional--;
		swap = prec->mantissa;
		just_zeroes = just_zeroes && (last_digit == 0);
		prec->mantissa = bi_div_small(prec->mantissa, 10, &last_digit);
		bi_destroy(swap);
		index++;
	}
	if (last_digit > 5 || (last_digit == 5 && !just_zeroes)
		|| (last_digit == 5 && (prec->mantissa->data[0] & 1)))
	{
		swap = prec->mantissa;
		prec->mantissa = bi_sum_small(prec->mantissa, 1);
		bi_destroy(swap);
	}
}

int				scale_to_int(t_precise *precise)
{
	ssize_t		index;
	t_bigint	*swap;

	index = 0;
	while (index < precise->fractional)
	{
		swap = precise->mantissa;
		if (!(precise->mantissa = bi_mul_small(swap, 5)))
			return (-1);
		bi_destroy(swap);
		index++;
	}
	precise->exponent = 0;
	return (0);
}

static char		*print_bigint(t_bigint **bi, ssize_t digits)
{
	char		*str;
	t_bigint	*bi_swap;
	uint32_t	mod;
	ssize_t		index;

	str = ft_strnew(0);
	index = 0;
	while ((digits >= 0 && index < digits)
		|| (digits < 0 && ((*bi)->size > 1 || (*bi)->data[0])))
	{
		bi_swap = (*bi);
		(*bi) = bi_div_small(bi_swap, 10, &mod);
		bi_destroy(bi_swap);
		str = string_add_char(mod + '0', str);
		index++;
	}
	if (digits < 0 && index == 0)
		str = string_add_char('0', str);
	return (str);
}

static char		*print_fract(t_precise *precise, ssize_t precision)
{
	ssize_t		index;
	char		*swap_str;
	char		*str;

	str = ft_strnew(0);
	index = 0;
	while (index < precision - precise->fractional)
	{
		str = string_add_char('0', str);
		index++;
	}
	swap_str = print_bigint(&precise->mantissa, precision - index);
	str = string_add(swap_str, str);
	free(swap_str);
	return (str);
}

char			*print_float(const t_conv *conv, t_precise *precise)
{
	char		*swap_str;
	char		*str;
	ssize_t		precision;

	precision = ((conv->precision < 0) ? 6 : conv->precision);
	round_to_even(precise, precise->fractional - precision);
	str = print_fract(precise, precision);
	if (conv->flags.alt_form || ft_strlen(str))
		str = string_add_char('.', str);
	swap_str = print_bigint(&precise->mantissa, -1);
	str = string_add(swap_str, str);
	free(swap_str);
	while (conv->flags.padding == PADDING_ZERO
		&& ft_strlen(str) + precise->flags.sign < conv->field_width)
		str = string_add_char('0', str);
	if (precise->flags.sign)
		str = string_add_char('-', str);
	else if (conv->flags.sign)
		str = string_add_char((conv->flags.sign == SIGN_GAP) ? ' ' : '+', str);
	return (str);
}
