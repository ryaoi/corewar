/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:46:43 by aamadori          #+#    #+#             */
/*   Updated: 2019/06/04 13:08:10 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		divisor;
	char	first_digit;

	if (n < 0)
		ft_putchar_fd('-', fd);
	divisor = 1000000000;
	first_digit = 0;
	while (divisor > 0)
	{
		if (first_digit || ft_abs(n / divisor) > 0)
		{
			ft_putchar_fd(ft_abs(n / divisor) + '0', fd);
			n -= (n / divisor) * divisor;
			first_digit = 1;
		}
		divisor /= 10;
	}
	if (!first_digit)
		ft_putchar_fd('0', fd);
}
