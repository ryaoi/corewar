/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_u_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:53:08 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/13 14:40:44 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <wchar.h>
#include <stdarg.h>

static char		*take_arg(const t_conv *conv, va_list *ap)
{
	wint_t			wide_character;
	char			*str;

	str = NULL;
	if (conv->length_modifier == l_long
		|| conv->flags.uppercase)
	{
		str = ft_strnew(4);
		if (str)
		{
			wide_character = va_arg(*ap, wint_t);
			ft_witomb(str, wide_character);
		}
	}
	else
	{
		str = ft_strnew(1);
		if (str)
			str[0] = va_arg(*ap, int);
	}
	return (str);
}

static char		*fit_width(const t_conv *conv, char *str)
{
	while (str && ft_strlen(str) < conv->field_width)
	{
		if (conv->flags.padding == PADDING_LEFT)
			str = string_append_char(str, ' ');
		else if (conv->flags.padding == PADDING_ZERO)
			str = string_add_char('0', str);
		else
			str = string_add_char(' ', str);
	}
	return (str);
}

t_string		*h_u_char(const t_conv *conv, va_list *ap)
{
	t_string	*ret;
	size_t		position;

	ret = ft_memalloc(sizeof(t_string));
	if (!ret)
		return (NULL);
	ret->size = -1;
	ret->buff = take_arg(conv, ap);
	if (ret->buff)
	{
		if (!ft_strlen(ret->buff))
			ret->buff[0] = '\xff';
		ret->buff = fit_width(conv, ret->buff);
		if (ret->buff)
		{
			ret->size = ft_strlen(ret->buff);
			position = (conv->flags.padding == PADDING_LEFT) ?
				0 : ret->size - 1;
			if (ret->buff[position] == '\xff')
				ret->buff[position] = '\0';
		}
	}
	return (ret);
}
