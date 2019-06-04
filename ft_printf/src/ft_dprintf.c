/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:15:07 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/26 18:05:49 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_dprintf_va(int fd, const char *format, va_list *ap)
{
	int				ret;
	t_target_info	info;

	ft_bzero(&info, sizeof(info));
	info.type = TYPE_FILE;
	info.target.fd = fd;
	ret = ft_printf_list(&info, &format, ap);
	return (ret);
}

int				ft_dprintf(int fd, const char *format, ...)
{
	va_list			ap;
	int				ret;

	va_start(ap, format);
	ret = ft_dprintf_va(fd, format, &ap);
	va_end(ap);
	return (ret);
}
