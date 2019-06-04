/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 21:55:13 by aamadori          #+#    #+#             */
/*   Updated: 2019/06/04 13:08:10 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

t_spec_match	g_specifiers[] = {
	{"d", h_s_dec},
	{"i", h_s_dec},
	{"u", h_u_dec},
	{"o", h_u_oct},
	{"x", h_u_hex},
	{"b", h_u_bin},
	{"c", h_u_char},
	{"s", h_string},
	{"p", h_pointer},
	{"f", h_float},
	{"%", h_percent}
};

t_length_match	g_lengths[] = {
	{"hh", l_char},
	{"ll", l_longlong},
	{"h", l_short},
	{"l", l_long},
	{"L", l_longdouble},
	{"z", l_size},
	{"j", l_max_type}
};

int		parse_flags(const char **format, t_conv *conv)
{
	while (**format == '#' || **format == '0' || **format == '-'
			|| **format == ' ' || **format == '+' || **format == '\'')
	{
		if (**format == '#')
			conv->flags.alt_form = ALTERNATE_SOFT;
		else if (**format == '0' && !conv->flags.padding)
			conv->flags.padding = PADDING_ZERO;
		else if (**format == '-')
			conv->flags.padding = PADDING_LEFT;
		else if (**format == ' ' && !conv->flags.sign)
			conv->flags.sign = SIGN_GAP;
		else if (**format == '+')
			conv->flags.sign = SIGN_PLUS;
		else if (**format == '\'')
			conv->flags.thousand_grouping = 1;
		(*format)++;
	}
	return (0);
}

int		parse_width(const char **format, va_list *ap, t_conv *conv)
{
	int		arg;

	arg = 0;
	if (**format == '*')
	{
		arg = va_arg(*ap, int);
		if (arg < 0)
			conv->flags.padding = PADDING_LEFT;
		(*format)++;
	}
	else
	{
		while (ft_isdigit(**format))
			arg = (arg * 10) + *((*format)++) - '0';
	}
	conv->field_width = ft_abs(arg);
	return (0);
}

int		parse_precision(const char **format, va_list *ap, t_conv *conv)
{
	int		arg;
	char	negative;

	conv->precision = -1;
	if (**format == '.')
	{
		arg = 0;
		conv->precision = 0;
		(*format)++;
		if (**format == '*')
		{
			arg = va_arg(*ap, int);
			(*format)++;
		}
		else
		{
			negative = (**format == '-') ? -1 : 1;
			if (**format == '-')
				(*format)++;
			while (ft_isdigit(**format))
				arg = ((arg * 10) + *((*format)++) - '0') * negative;
		}
		conv->precision = (arg < 0) ? -1 : arg;
	}
	return (0);
}

int		parse_length(const char **format, t_conv *conv)
{
	size_t index;

	index = 0;
	while (index < sizeof(g_lengths) / sizeof(g_lengths[0]))
	{
		if (!ft_strncmp(*format, g_lengths[index].string,
					ft_strlen(g_lengths[index].string)))
		{
			conv->length_modifier = g_lengths[index].length;
			*format += ft_strlen(g_lengths[index].string);
		}
		index++;
	}
	return (0);
}

int		parse_specifier(const char **format, t_conv *conv)
{
	size_t	index;

	index = 0;
	while (index < (sizeof(g_specifiers) / sizeof(g_specifiers[0])))
	{
		if (**format == g_specifiers[index].string[0]
			|| **format == g_specifiers[index].string[0] + ('A' - 'a'))
		{
			if (ft_isupper(**format))
				conv->flags.uppercase = 1;
			conv->handler = g_specifiers[index].specifier;
			*format += ft_strlen(g_specifiers[index].string);
			return (0);
		}
		index++;
	}
	return (-1);
}
