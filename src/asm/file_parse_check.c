/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:11:46 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/21 19:49:06 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_token_type(t_token *token, char *str)
{
	size_t	len;

	if (!(len = ft_strlen(str)))
		return (TOKEN_TYPE_FAIL);
	if (token->id == 0)
	{
		if (str[len - 1] == LABEL_CHAR)
			token->type = e_label;
		else
			token->type = e_instr;
	}
	else if (len > 2 && str[0] == DIRECT_CHAR && str[1] == LABEL_CHAR)
		token->type = e_dirlab;
	else if (len > 1 && str[0] == DIRECT_CHAR && is_str_digit(str + 1))
		token->type = e_direct;
	else if (len > 1 && str[0] == REGISTER_CHAR && is_str_digit(str + 1))
		token->type = e_register;
	else if (str[0] == LABEL_CHAR)
		token->type = e_indirlab;
	else if (is_str_digit(str))
		token->type = e_indirect;
	else
		return (TOKEN_TYPE_FAIL);
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
			return (TOKEN_LABEL_SYNTAX_FAIL);
		index++;
	}
	return (SUCCESS);
}

int		check_register(char *str)
{
	if (ft_atoi(str + 1) > REG_NUMBER || ft_atoi(str + 1) < 1)
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
				return (e_malloc_fail);
			ft_memcpy(token->op, &g_op_tab[index], sizeof(t_op));
			return (SUCCESS);
		}
		index++;
	}
	return (TOKEN_INSTR_INVALID);
}
