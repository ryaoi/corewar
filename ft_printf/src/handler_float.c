/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:53:37 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/13 12:44:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "bigint.h"
#include "handler_float.h"
#include <stdint.h>
#include <stdarg.h>

const char	*g_special_values[] = {
	"inf",
	"-inf",
	"INF",
	"-INF",
	"nan",
	"-nan",
	"NAN",
	"-NAN"
};

static char		*handle_special(const t_conv *conv, t_precise *precise)
{
	size_t	index;

	if (precise->flags.exponent == FULL)
	{
		if (precise->flags.mantissa)
			index = 4;
		else
			index = 0;
		index += 2 * conv->flags.uppercase;
		index += precise->flags.sign ? 1 : 0;
		return (ft_strdup(g_special_values[index]));
	}
	return (NULL);
}

static char		*resolve(const t_conv *conv, va_list *ap)
{
	double			d;
	long double		ld;
	t_precise		precise;
	char			*str;
	int				error;

	str = NULL;
	if (conv->length_modifier == l_longdouble)
	{
		ld = va_arg(*ap, long double);
		error = float_80(ld, &precise);
	}
	else
	{
		d = va_arg(*ap, double);
		error = float_64(d, &precise);
	}
	if (!error && !(str = handle_special(conv, &precise)))
		str = print_float(conv, &precise);
	bi_destroy(precise.mantissa);
	return (str);
}

static char		*fit_width(const t_conv *conv, char *str)
{
	while (str && ft_strlen(str) < conv->field_width)
	{
		if (conv->flags.padding == PADDING_LEFT)
			str = string_append_char(str, ' ');
		else
			str = string_add_char(' ', str);
	}
	return (str);
}

t_string		*h_float(const t_conv *conv, va_list *ap)
{
	t_string	*ret;

	ret = ft_memalloc(sizeof(t_string));
	if (!ret)
		return (NULL);
	ret->buff = resolve(conv, ap);
	ret->size = -1;
	if (ret->buff && (ret->buff = fit_width(conv, ret->buff)))
		ret->size = ft_strlen(ret->buff);
	return (ret);
}
