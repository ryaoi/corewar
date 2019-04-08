/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:11:06 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 15:18:21 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_comment(t_line *line)
{
	int	index;

	index = 0;
	while (line->str && line->str[index] && ft_isspace(line->str[index]))
		index++;
	if (line->str[index] == COMMENT_CHAR)
		return (1);
	return (0);
}

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
	token->type = T_UNKNOWN;
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
