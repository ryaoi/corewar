/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 16:44:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/26 18:04:35 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H

# include <sys/types.h>
# include <inttypes.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "bigint.h"

# define FTPRINTF_BUFF_SIZE 4096

extern char				g_flusher_char;

enum					e_length
{
	l_default = 0,
	l_char,
	l_short,
	l_long,
	l_longlong,
	l_longdouble,
	l_ptr,
	l_size,
	l_max_type
};

typedef struct s_conv	t_conv;

typedef struct			s_string
{
	ssize_t	size;
	char	*buff;
}						t_string;

typedef t_string		*(*t_handler)(const t_conv* conv, va_list *ap);

typedef struct			s_spec_match
{
	char		*string;
	t_handler	specifier;
}						t_spec_match;

typedef struct			s_length_match
{
	char			*string;
	enum e_length	length;
}						t_length_match;

# define ALTERNATE_SOFT 1
# define ALTERNATE_FORCE 2
# define PADDING_ZERO 1
# define PADDING_LEFT 2
# define SIGN_GAP 1
# define SIGN_PLUS 2

typedef struct			s_flags
{
	char	alt_form;
	char	padding;
	char	sign;
	char	thousand_grouping;
	char	uppercase;
}						t_flags;

struct					s_conv
{
	t_handler	handler;
	t_flags		flags;
	size_t		field_width;
	ssize_t		precision;
	char		length_modifier;
};

# define TYPE_FILE 1
# define TYPE_BUFFER 2

typedef struct			s_target_info
{
	char	type;
	union				u_target
	{
		int		fd;
		char	*buff;
	}		target;
	size_t	max_size;
	size_t	index;
}						t_target_info;

extern char				*g_dec_base;
extern char				*g_hex_base;
extern char				*g_hex_base_up;
extern char				*g_oct_base;
extern char				*g_bin_base;

int						ft_printf_list(t_target_info *info,
							const char **format, va_list *ap);
int						ft_printf(const char *format, ...);
int						ft_printf_va(const char *format, va_list *ap);
int						ft_dprintf(int fd, const char *format, ...);
int						ft_dprintf_va(int fd, const char *format, va_list *ap);
int						ft_snprintf(char *const buff, size_t size,
							const char *format, ...);
int						ft_snprintf_va(char *const buff, size_t size,
							const char *format, va_list *ap);
void					ft_fflush();

void					print_to_target(t_target_info *info,
							const char *str, ssize_t size);
void					string_destroy(t_string *data);
char					*string_add(const char *more, char *str);
char					*string_append(char *str, const char *more);
char					*string_append_char(char *str, char c);
char					*string_add_char(char c, char *str);
char					*s_base_conv(const t_conv *conv, intmax_t n,
							const char *base, size_t min_dig);
char					*u_base_conv(const t_conv *conv, uintmax_t n,
							const char *base, size_t min_dig);

t_string				*h_s_dec(const t_conv *conv, va_list *ap);
t_string				*h_u_dec(const t_conv *conv, va_list *ap);
t_string				*h_u_oct(const t_conv *conv, va_list *ap);
t_string				*h_u_hex(const t_conv *conv, va_list *ap);
t_string				*h_u_bin(const t_conv *conv, va_list *ap);
t_string				*h_u_char(const t_conv *conv, va_list *ap);
t_string				*h_string(const t_conv *conv, va_list *ap);
t_string				*h_pointer(const t_conv *conv, va_list *ap);
t_string				*h_float(const t_conv *conv, va_list *ap);
t_string				*h_percent(const t_conv *conv, va_list *ap);

int						parse_flags(const char **format, t_conv *conv);
int						parse_width(const char **format, va_list *ap,
							t_conv *conv);
int						parse_precision(const char **format, va_list *ap,
							t_conv *conv);
int						parse_length(const char **format, t_conv *conv);
int						parse_specifier(const char **format, t_conv *conv);

#endif
