/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:41:28 by aamadori          #+#    #+#             */
/*   Updated: 2019/06/04 13:08:10 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	digits(int n)
{
	size_t	digits;

	digits = 1;
	while (ft_abs(n) > 9)
	{
		n /= 10;
		digits++;
	}
	if (n >= 0)
		return (digits);
	else
		return (digits + 1);
}

static void		generate_string(char *str, int n)
{
	size_t	str_index;
	int		divisor;
	char	first_digit;

	str_index = 0;
	if (n < 0)
		str[str_index++] = '-';
	divisor = 1000000000;
	first_digit = 0;
	while (divisor > 0)
	{
		if (first_digit || ft_abs(n / divisor) > 0)
		{
			str[str_index++] = ft_abs(n / divisor) + '0';
			n -= (n / divisor) * divisor;
			first_digit = 1;
		}
		divisor /= 10;
	}
	if (!first_digit)
		str[str_index] = '0';
}

char			*ft_itoa(int n)
{
	char	*str;

	str = ft_strnew(digits(n));
	if (!str)
		return (NULL);
	generate_string(str, n);
	return (str);
}
