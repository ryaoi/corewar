/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 13:03:21 by aamadori          #+#    #+#             */
/*   Updated: 2019/02/08 23:19:11 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include <unistd.h>

char		g_general_buffer[FTPRINTF_BUFF_SIZE];
t_buffer	g_buffer_info = {g_general_buffer, 0, FTPRINTF_BUFF_SIZE};
char		g_flusher_char = '\n';

void		ft_fflush(void)
{
	write(1, g_buffer_info.buffer, g_buffer_info.index);
	g_buffer_info.index = 0;
}

static void	print_to_stdout(const char *str, size_t bytes)
{
	static char		init = 0;
	size_t			index;

	if (!init)
	{
		ft_memset(g_general_buffer, 0, FTPRINTF_BUFF_SIZE);
		init = 1;
	}
	index = 0;
	while (index < bytes)
	{
		g_buffer_info.buffer[g_buffer_info.index] = str[index];
		g_buffer_info.index++;
		if (str[index] == g_flusher_char
			|| g_buffer_info.index == FTPRINTF_BUFF_SIZE)
			ft_fflush();
		index++;
	}
}

void		print_to_target(t_target_info *info,
				const char *str, ssize_t size)
{
	size_t			bytes;

	bytes = (size < 0) ? ft_strlen(str) : (size_t)size;
	if (info->type == TYPE_BUFFER)
	{
		if (info->target.buff && info->index < info->max_size)
			ft_memcpy(info->target.buff + info->index, str,
				ft_min(bytes, info->max_size - info->index));
	}
	else if (info->type == TYPE_FILE)
		write(info->target.fd, str, bytes);
	else
		print_to_stdout(str, bytes);
	info->index += bytes;
}
