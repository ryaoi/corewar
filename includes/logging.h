/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:50:46 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/28 14:03:11 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LOGGING_H
# define _LOGGING_H
# include <stdint.h>
# include <stdarg.h>
# include "ft_printf.h"
# include "array.h"

enum	e_log_level
{
	e_log_lives = 0,
	e_log_cycles,
	e_log_instr,
	e_log_store,
	e_log_load,
	e_log_deaths,
	e_log_memdump,
	e_log_level_max
};

enum	e_log_mode
{
	e_mode_stdout = 0,
	e_mode_stderr,
	e_mode_save
};

typedef struct		s_log_string
{
	char	*string;
	size_t	id;
}					t_log_string;

typedef struct		s_log_info
{
	enum e_log_level	log_levels;
	enum e_log_mode		log_mode;
	size_t				logs_num;
	t_array				logs[e_log_level_max];
}					t_log_info;

/* TODO actually log everything */
void	log_level_va(t_log_info *info, uint64_t type, const char *format,
			va_list *ap);
void	log_level(t_log_info *info, uint64_t type, const char *format, ...);
void	logs_init(t_log_info *info);

#endif
