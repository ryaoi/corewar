/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:43:27 by aamadori          #+#    #+#             */
/*   Updated: 2019/06/04 15:05:11 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*g_dec_base = "0123456789";
char	*g_hex_base = "0123456789abcdef";
char	*g_hex_base_up = "0123456789ABCDEF";
char	*g_oct_base = "01234567";
char	*g_bin_base = "01";

static size_t	s_digits(intmax_t n, ssize_t b_size,
					uint8_t thousand, size_t min_dig)
{
	size_t		size;
	intmax_t	n_orig;

	n_orig = n;
	size = 0;
	while (ft_abs(n) > 0)
	{
		n /= b_size;
		size++;
		if (thousand && b_size == 10 && size > 0 && (size % 3) == 0)
			size++;
	}
	return (ft_max(size, min_dig) + ((n_orig < 0) ? 1 : 0));
}

char			*s_base_conv(const t_conv *conv,
					intmax_t n, const char *base, size_t min_dig)
{
	ssize_t		b_size;
	size_t		dig_index;
	size_t		str_index;
	size_t		len;
	char		*string;

	b_size = ft_strlen(base);
	if (b_size == 10 && conv->flags.thousand_grouping)
		min_dig += ((min_dig - 1) / 3);
	len = s_digits(n, b_size, conv->flags.thousand_grouping, min_dig);
	string = ft_strnew(len);
	dig_index = 0;
	str_index = 0;
	if (n < 0)
		string[str_index++] = '-';
	while (dig_index < min_dig || ft_abs(n) > 0 || ft_abs(n / b_size) > 0)
	{
		if (conv->flags.thousand_grouping
			&& b_size == 10 && dig_index > 0 && (dig_index % 3) == 0)
			string[len - 1 - (str_index++)] = ',';
		string[len - 1 - (str_index++)] = base[ft_abs(n - (n / b_size) * b_size)];
		n = n / b_size;
		dig_index++;
	}
	return (string);
}

static size_t	u_digits(uintmax_t n, size_t b_size,
					uint8_t thousand, size_t min_dig)
{
	size_t	size;

	size = 0;
	while (n > 0)
	{
		n /= b_size;
		size++;
		if (thousand && b_size == 10 && size % 3 == 0)
			size++;
	}
	return (ft_max(size, min_dig));
}

char			*u_base_conv(const t_conv *conv,
					uintmax_t n, const char *base, size_t min_dig)
{
	size_t		b_size;
	size_t		dig_index;
	size_t		str_index;
	size_t		len;
	char		*string;

	b_size = ft_strlen(base);
	if (b_size == 10 && conv->flags.thousand_grouping)
		min_dig += ((min_dig - 1) / 3);
	len = u_digits(n, b_size, conv->flags.thousand_grouping, min_dig);
	string = ft_strnew(len);
	dig_index = 0;
	str_index = 0;
	while (dig_index < min_dig || n > 0 || n / b_size > 0)
	{
		if (conv->flags.thousand_grouping
			&& b_size == 10 && dig_index > 0 && (dig_index % 3) == 0)
			string[len - 1 - (str_index++)] = ',';
		string[len - 1 - (str_index++)] = base[n - (n / b_size) * b_size];
		n = n / b_size;
		dig_index++;
	}
	return (string);
}
