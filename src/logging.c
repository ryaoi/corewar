/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:22:00 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/01 15:06:03 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"

static void	log_save(t_log_info *info, uint64_t type,
				const char *format, va_list *ap)
{
	t_log_string	log;

	if (type >= e_log_level_max)
		return ;
	log.string = ft_memalloc(1024);
	ft_snprintf_va(log.string, 1024, format, ap);
	log.id = info->logs_num;
	array_push_back(&info->logs[type], &log);
}

void	log_level_va(t_log_info *info, uint64_t type,
			const char *format, va_list *ap)
{
	if (info->log_active[type])
	{
		if (info->log_mode == e_mode_stdout)
		{
			ft_printf_va(format, ap);
			ft_printf("\n");
		}
		else if (info->log_mode == e_mode_stderr)
		{
			ft_dprintf_va(2, format, ap);
			ft_dprintf_va(2, "\n", ap);
		}
		else if (info->log_mode == e_mode_save)
		{
			log_save(info, type, format, ap);
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
	while (index < e_log_level_max)
	{
		array_init(&info->logs[index], sizeof(t_log_string));
		index++;
	}
}

void	log_string_destroy(void *ptr)
{
	t_log_string	*string;

	string = ptr;
	free(string->string);
	string->string = NULL;
}

void	logs_destroy(t_log_info *info)
{
		size_t	index;

	index = 0;
	while (index < e_log_level_max)
	{
		array_clear(&info->logs[index], log_string_destroy);
		index++;
	}
}
