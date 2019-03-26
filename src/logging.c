/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:22:00 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/26 18:35:01 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

static void	log_to_python(t_log_info *info, uint64_t type,
				const char *format, va_list *ap)
{
	size_t			log_index;
	t_log_string	log;

	log_index = 0;
	while (type)
	{
		type /= 2;
		log_index++;
	}
	if (!log_index)
		return ;
	log_index--;
	log.string = ft_memalloc(1024);
	ft_snprintf_va(log.string, 1024, format, ap);
	log.id = info->logs_num;
	array_push_back(&info->logs[log_index], &log);
}

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
		else if (info->log_mode == LOG_PYTHON)
		{
			log_to_python(info, type, format, ap);
		}
	}
	info->logs_num++;
}

void	log_level(t_log_info *info, uint64_t type, const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	log_level_va(info, type, format, &ap);
	va_end(ap);
}

void	logs_init(t_log_info *info)
{
	size_t	index;

	index = 0;
	ft_bzero(info, sizeof(t_log_info));
	while (index < 64)
	{
		array_init(&info->logs[index], sizeof(t_log_string));
		index++;
	}
}
