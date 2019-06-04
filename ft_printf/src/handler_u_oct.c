/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_u_oct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:52:34 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/13 13:05:20 by aamadori         ###   ########.fr       */
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
	if (conv->length_modifier == l_char && !conv->flags.uppercase)
		return ((unsigned char)va_arg(*ap, unsigned int));
	else if (conv->length_modifier == l_short && !conv->flags.uppercase)
		return ((unsigned short)va_arg(*ap, unsigned int));
	else if (conv->length_modifier == l_long || conv->flags.uppercase)
		return (va_arg(*ap, unsigned long));
	else if (conv->length_modifier == l_longlong)
		return (va_arg(*ap, unsigned long long));
	else if (conv->length_modifier == l_size)
		return (va_arg(*ap, size_t));
	else if (conv->length_modifier == l_max_type)
		return (va_arg(*ap, uintmax_t));
	return (va_arg(*ap, unsigned int));
}

t_string			*h_u_oct(const t_conv *conv, va_list *ap)
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
	ret->buff = u_base_conv(conv, arg, g_oct_base, min_digits);
	while (ret->buff && conv->precision < 0
			&& conv->flags.padding == PADDING_ZERO
			&& ft_strlen(ret->buff) < conv->field_width)
		ret->buff = string_add("0", ret->buff);
	if (ret->buff && conv->flags.alt_form && ret->buff[0] != '0')
		ret->buff = string_add("0", ret->buff);
	ret->size = -1;
	if (ret->buff && (ret->buff = padding(ret->buff, conv)))
		ret->size = ft_strlen(ret->buff);
	return (ret);
}
