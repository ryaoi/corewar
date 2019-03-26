/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 15:20:56 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/26 16:59:16 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assert.h"
#include "ft_printf.h"

void	ft_assert(char cond, const char *message)
{
	if (!cond)
	{
		ft_dprintf(2, "Assert failed: %s\n", message);
		exit(0);
	}
}
