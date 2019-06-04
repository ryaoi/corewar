/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 23:36:40 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/13 12:45:19 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static char	*fit_width(char *str, const t_conv *conv)
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

t_string	*h_percent(const t_conv *conv, va_list *ap)
{
	t_string	*ret;

	(void)(ap);
	ret = ft_memalloc(sizeof(t_string));
	if (!ret)
		return (NULL);
	ret->buff = ft_strnew(1);
	ret->size = -1;
	if (ret->buff)
	{
		ret->buff[0] = '%';
		if ((ret->buff = fit_width(ret->buff, conv)))
			ret->size = ft_strlen(ret->buff);
	}
	return (ret);
}
