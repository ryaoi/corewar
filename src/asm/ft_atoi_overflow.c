/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_overflow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:41:46 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/05 16:44:00 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static size_t	skip_ws(const char *str)
{
	size_t index;

	index = 0;
	while (str[index] && ft_isspace(str[index]))
		index++;
	return (index);
}

int	ft_atoi_overflow(const char *str)
{
	size_t	index;
	int		result;
	int		tmp;
	int		sign;

	result = 0;
	sign = 1;
	index = skip_ws(str);
	if (str[index] == '-')
		sign = -1;
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index] && ft_isdigit(str[index]))
	{
		tmp = result;
		result *= 10;
		result = result + (str[index] - '0');
		if (result < tmp)
			return (sign == 1 ? INT_MAX : 0);
		index++;
	}
	return (result * sign);
}
