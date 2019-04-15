/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:11:46 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/15 18:26:05 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_token_type(t_token *token, char *str)
{
	size_t	len;
	if (!(len = ft_strlen(str)))
	{
		printf("waht the fuck : %s\n", token->str);
		return (TOKEN_TYPE_FAIL);
	}
	if (token->id == 0)
	{
		if (str[len - 1] == LABEL_CHAR)
			token->type = T_LABEL;
		else
			token->type = T_INSTR;
	}
	else if (len > 2 && str[0] == DIRECT_CHAR && str[1] == LABEL_CHAR)
		token->type = T_DIRLAB;
	else if (len > 1 && str[0] == DIRECT_CHAR && is_str_digit(str + 1))
		token->type = T_DIRECT;
	else if (len > 1 && str[0] == REGISTER_CHAR && is_str_digit(str + 1))
		token->type = T_REGISTER;
	else if (str[0] == LABEL_CHAR)
		token->type = T_INDIRLAB;
	else if (is_str_digit(str))
		token->type = T_INDIRECT;
	else
	{
		printf("%s\n", token->str);
		return (TOKEN_TYPE_FAIL);
	}
	return (SUCCESS);
}

int		check_label_syntax(char *str)
{
	int index;

	index = 0;
	while (str[index])
	{
		if (!ft_strchr(LABEL_CHARS, str[index]) &&
			!(index == 0 && str[index] == DIRECT_CHAR) &&
				!((index == 0 | index == 1) && str[index] == LABEL_CHAR))
			{
				printf("error line : %s\n", str);
				return (TOKEN_LABEL_SYNTAX_FAIL);
			}
		index++;
	}
	return (SUCCESS);
}

int		check_register(char *str)
{
	if (ft_atoi(str + 1) > REG_NUMBER)
		return (TOKEN_REGISTER_FAIL);
	return (SUCCESS);
}

int		check_instr(t_token *token, char *str)
{
	int	index;

	index = 0;
	while (index < 16)
	{
		if (!ft_strcmp(str, g_op_tab[index].name))
		{
			if (!(token->op = (t_op*)malloc(sizeof(t_op))))
				return (MALLOC_FAIL);
			ft_memcpy(token->op, &g_op_tab[index], sizeof(t_op));
			return (SUCCESS);
		}
		index++;
	}
	return (TOKEN_INSTR_INVALID);
}
