/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 18:09:10 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/28 17:43:06 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_assert.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	substr = NULL;
	if (s)
	{
		substr = malloc(len + 1);
		ft_malloc_assert(substr);
		if (substr)
		{
			ft_memcpy(substr, s + start, len);
			substr[len] = '\0';
		}
	}
	return (substr);
}
