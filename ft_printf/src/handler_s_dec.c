/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_s_dec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:49:36 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/13 14:53:33 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdarg.h>

static char		*padding(char *str, const t_conv *conv)
{
	while (str && ft_strlen(str) < conv->field_width)
	{
		if (conv->flags.padding == PADDING_LEFT)
			str = string_append(str, " ");
		else
			str = string_add(" ", str);
	}
	return (str);
}

static intmax_t	take_arg(const t_conv *conv, va_list *ap)
{
	if (conv->length_modifier == l_char && !conv->flags.uppercase)
		return ((char)va_arg(*ap, int));
	else if (conv->length_modifier == l_short && !conv->flags.uppercase)
		return ((short)va_arg(*ap, int));
	else if (conv->length_modifier == l_long || conv->flags.uppercase)
		return (va_arg(*ap, long));
	else if (conv->length_modifier == l_longlong)
		return (va_arg(*ap, long long));
	else if (conv->length_modifier == l_size)
		return (va_arg(*ap, ssize_t));
	else if (conv->length_modifier == l_max_type)
		return (va_arg(*ap, intmax_t));
	return (va_arg(*ap, int));
}

t_string		*h_s_dec(const t_conv *conv, va_list *ap)
{
	t_string		*ret;
	intmax_t		arg;
	size_t			min_digits;

	ret = ft_memalloc(sizeof(t_string));
	if (!ret)
		return (NULL);
	arg = take_arg(conv, ap);
	min_digits = conv->precision >= 0 ? conv->precision : 1;
	ret->buff = s_base_conv(conv, arg, g_dec_base, min_digits);
	while (ret->buff && conv->precision < 0
			&& conv->flags.padding == PADDING_ZERO
			&& ft_strlen(ret->buff)
				+ ((arg < 0 || conv->flags.sign) ? 1 : 0) < conv->field_width)
		ret->buff = string_add("0", ret->buff);
	if (ret->buff && arg < 0)
		ret->buff = string_add("-", ret->buff);
	else if (ret->buff && conv->flags.sign)
		ret->buff =
			string_add(conv->flags.sign == SIGN_PLUS ? "+" : " ", ret->buff);
	ret->size = -1;
	if (ret->buff && (ret->buff = padding(ret->buff, conv)))
		ret->size = ft_strlen(ret->buff);
	return (ret);
}
