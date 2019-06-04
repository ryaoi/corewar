/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:17:26 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/26 18:05:59 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_snprintf_va(char *const buff, size_t size,
				const char *format, va_list *ap)
{
	int				ret;
	t_target_info	info;

	ft_bzero(&info, sizeof(info));
	info.type = TYPE_BUFFER;
	info.target.buff = buff;
	info.max_size = size - 1;
	ret = ft_printf_list(&info, &format, ap);
	if (buff && info.index < size)
		buff[info.index] = '\0';
	return (ret);
}

int			ft_snprintf(char *const buff, size_t size,
				const char *format, ...)
{
	va_list			ap;
	int				ret;

	va_start(ap, format);
	ret = ft_snprintf_va(buff, size, format, &ap);
	va_end(ap);
	return (ret);
}
