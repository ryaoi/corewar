/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:53:19 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/13 12:45:32 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <stdarg.h>

static char		*handle_wide(wchar_t *wide_str, const t_conv *conv)
{
	char		*str;
	char		swap_str[4];
	size_t		index;

	str = ft_strnew(0);
	index = 0;
	while (str
		&& wide_str[index])
	{
		ft_bzero(swap_str, 4);
		ft_witomb(swap_str, wide_str[index]);
		if (conv->precision >= 0
			&& ft_strlen(str) + ft_strlen(swap_str) > (size_t)conv->precision)
			return (str);
		str = string_append(str, swap_str);
		index++;
	}
	return (str);
}

static char		*take_arg(const t_conv *conv, va_list *ap)
{
	wchar_t			*wide_str;
	char			swap_str[4];
	char			*arg;
	char			*str;

	if (conv->length_modifier == l_long || conv->flags.uppercase)
	{
		ft_bzero(swap_str, 4);
		if (!(wide_str = va_arg(*ap, wchar_t*)))
			return (NULL);
		str = handle_wide(wide_str, conv);
	}
	else
	{
		if (!(arg = va_arg(*ap, char*)))
			return (NULL);
		str = ft_strnew(conv->precision >= 0 ?
			(size_t)conv->precision : ft_strlen(arg));
		if (str && conv->precision >= 0)
			ft_strncpy(str, arg, conv->precision);
		else if (str)
			ft_strcpy(str, arg);
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

t_string		*h_string(const t_conv *conv, va_list *ap)
{
	t_string	*ret;

	ret = ft_memalloc(sizeof(t_string));
	if (!ret)
		return (NULL);
	ret->buff = take_arg(conv, ap);
	if (!ret->buff)
	{
		if (conv->precision < 0)
			ret->buff = ft_strdup("(null)");
		else
			ret->buff = ft_strnew(0);
	}
	if (ret->buff && (ret->buff = fit_width(conv, ret->buff)))
		ret->size = ft_strlen(ret->buff);
	else
		ret->size = -1;
	return (ret);
}
