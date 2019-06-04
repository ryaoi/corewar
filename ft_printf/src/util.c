/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 22:14:17 by aamadori          #+#    #+#             */
/*   Updated: 2018/12/13 13:25:05 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	string_destroy(t_string *data)
{
	free(data->buff);
	free(data);
}

char	*string_add_char(char c, char *str)
{
	char	*swap;

	swap = str;
	str = ft_strnew(ft_strlen(str) + 1);
	if (str)
	{
		ft_memcpy(str + 1, swap, ft_strlen(swap));
		str[0] = c;
	}
	free(swap);
	return (str);
}

char	*string_add(const char *more, char *str)
{
	char *swap;

	swap = str;
	str = ft_strjoin(more, str);
	free(swap);
	return (str);
}

char	*string_append_char(char *str, char c)
{
	char	*swap;

	swap = str;
	str = ft_strnew(ft_strlen(str) + 1);
	if (str)
	{
		ft_memcpy(str, swap, ft_strlen(swap));
		str[ft_strlen(swap)] = c;
	}
	free(swap);
	return (str);
}

char	*string_append(char *str, const char *more)
{
	char *swap;

	swap = str;
	str = ft_strjoin(str, more);
	free(swap);
	return (str);
}
