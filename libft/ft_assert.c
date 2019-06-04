/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:20:56 by aamadori          #+#    #+#             */
/*   Updated: 2019/06/04 12:28:38 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"
#include "libft.h"

void	ft_assert(char cond, const char *message)
{
	if (!cond)
	{
		ft_putstr_fd("Assert failed: ", 2);
		ft_putendl_fd(message, 2);
		exit(0);
	}
}

void	ft_malloc_assert(void *ptr)
{
	char	cond;

	cond = !(!(ptr));
	ft_assert(cond, "Call to malloc returned NULL.");
}
