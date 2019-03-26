/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:50:46 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/26 18:04:06 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _LOGGING_H
# define _LOGGING_H
# include <stdint.h>
# include <stdarg.h>
# include "ft_printf.h"

# define LOG_LIVES 1
# define LOG_CYCLES 2
# define LOG_INSTR 4
# define LOG_DEATHS 8

# define LOG_STDOUT 0
# define LOG_PYTHON 1


typedef struct		s_log_info
{
	uint64_t	log_levels;
	uint8_t		log_mode;

}					t_log_info;

/* TODO implement */
void	log_level_va(t_log_info *info, uint64_t type, const char *format,
			va_list *ap);
void	log_level(t_log_info *info, uint64_t type, const char *format, ...);

#endif
