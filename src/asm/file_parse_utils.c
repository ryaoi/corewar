/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:11:06 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/27 14:52:49 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_str_digit(char *str)
{
	int	index;

	index = 0;
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (0);
		index++;
	}
	return (1);
}

void	init_token(t_token *token)
{
	token->id = -1;
	token->str = NULL;
	token->op = NULL;
	token->type = e_unknown;
	token->value = -1;
}

void	remove_label_char(char *str)
{
	int index;

	index = 0;
	while (str && str[index])
	{
		if (str[index] == LABEL_CHAR)
			str[index] = '\0';
		index++;
	}
}
