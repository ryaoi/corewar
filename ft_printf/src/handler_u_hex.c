/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_u_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:47:17 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/13 14:52:19 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdarg.h>

static char			*padding(char *str, const t_conv *conv)
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

static uintmax_t	take_arg(const t_conv *conv, va_list *ap)
{
	if (conv->length_modifier == l_char)
		return ((unsigned char)va_arg(*ap, unsigned int));
	else if (conv->length_modifier == l_short)
		return ((unsigned short)va_arg(*ap, unsigned int));
	else if (conv->length_modifier == l_long)
		return (va_arg(*ap, unsigned long));
	else if (conv->length_modifier == l_longlong)
		return (va_arg(*ap, unsigned long long));
	else if (conv->length_modifier == l_ptr)
		return ((uintmax_t)va_arg(*ap, void *));
	else if (conv->length_modifier == l_size)
		return (va_arg(*ap, size_t));
	else if (conv->length_modifier == l_max_type)
		return (va_arg(*ap, uintmax_t));
	return (va_arg(*ap, unsigned int));
}

t_string			*h_u_hex(const t_conv *conv, va_list *ap)
{
	t_string	*ret;
	uintmax_t	arg;
	size_t		min_digits;

	ret = ft_memalloc(sizeof(t_string));
	if (!ret)
		return (NULL);
	ret->size = 0;
	arg = take_arg(conv, ap);
	min_digits = conv->precision >= 0 ? conv->precision : 1;
	ret->buff = u_base_conv(conv, arg,
			(conv->flags.uppercase ? g_hex_base_up : g_hex_base), min_digits);
	ret->size = (conv->flags.alt_form == ALTERNATE_FORCE
		|| (conv->flags.alt_form && arg != 0)) ? 2 : 0;
	while (ret->buff && conv->precision < 0
			&& conv->flags.padding == PADDING_ZERO
			&& ft_strlen(ret->buff) + ret->size < conv->field_width)
		ret->buff = string_add("0", ret->buff);
	if (ret->buff && ret->size)
		ret->buff = string_add(conv->flags.uppercase ? "0X" : "0x", ret->buff);
	ret->size = -1;
	if (ret->buff && (ret->buff = padding(ret->buff, conv)))
		ret->size = ft_strlen(ret->buff);
	return (ret);
}
