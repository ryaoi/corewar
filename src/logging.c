/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:22:00 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/26 18:03:28 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

void	log_level_va(t_log_info *info, uint64_t type,
			const char *format, va_list *ap)
{
	if (info->log_levels & type)
	{
		if (info->log_mode == LOG_STDOUT)
		{
			ft_printf_va(format, ap);
			ft_printf("\n");
		}
		else
		{
			/* TODO */
			exit(1);
		}
	}
}

void	log_level(t_log_info *info, uint64_t type, const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	log_level_va(info, type, format, &ap);
	va_end(ap);
}
