/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:50:46 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/21 19:15:34 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LOGGING_H
# define _LOGGING_H
# include <stdint.h>
# include <stdarg.h>
# include "ft_printf.h"
# include "array.h"

enum			e_log_level
{
	e_log_lives = 0,
	e_log_cycles,
	e_log_instr,
	e_log_store,
	e_log_load,
	e_log_jump,
	e_log_fork,
	e_log_game,
	e_log_deaths,
	e_log_level_max
};

enum			e_log_mode
{
	e_mode_stdout = 0,
	e_mode_stderr,
	e_mode_save
};

typedef struct	s_log_string
{
	char	*string;
	size_t	id;
}				t_log_string;

typedef struct	s_log_info
{
	enum e_log_mode		log_mode;
	size_t				logs_num;
	t_array				logs[e_log_level_max];
	size_t				log_heads[e_log_level_max];
	uint8_t				log_active[e_log_level_max];
}				t_log_info;

void			log_save(t_log_info *info, uint64_t type,
					const char *format, va_list *ap);
void			log_level_va(t_log_info *info, uint64_t type,
					const char *format, va_list *ap);
void			log_level(t_log_info *info, uint64_t type,
					const char *format, ...);
void			logs_init(t_log_info *info);
void			log_string_destroy(void *ptr);
void			logs_destroy(t_log_info *info);

#endif
