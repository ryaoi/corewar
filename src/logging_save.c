/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging_save.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:03:26 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/20 15:03:51 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logging.h"
#include "ft_assert.h"

void	log_save(t_log_info *info, uint64_t type,
			const char *format, va_list *ap)
{
	t_log_string	log;

	if (type >= e_log_level_max)
		return ;
	log.string = malloc(1024);
	MALLOC_ASSERT(log.string);
	ft_snprintf_va(log.string, 1024, format, ap);
	log.id = info->logs_num;
	array_push_back(&info->logs[type], &log);
}
