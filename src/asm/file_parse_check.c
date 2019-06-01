/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:11:46 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/01 16:37:27 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_token_type(t_token *token, char *str)
{
	size_t	len;

	if (!(len = ft_strlen(str)))
		return (e_token_type_fail);
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
		token->type = e_dir;
	else if (len > 1 && str[0] == REGISTER_CHAR && is_str_digit(str + 1))
		token->type = e_reg;
	else if (str[0] == LABEL_CHAR)
		token->type = e_indirlab;
	else if (is_str_digit(str))
		token->type = e_indir;
	else
		return (e_token_type_fail);
	return (FT_SUCCESS);
}

int		check_label_syntax(char *str)
{
	int index;

	index = 0;
	while (str[index])
	{
		if (!ft_strchr(LABEL_CHARS, str[index])
			&& !(index == 0 && str[index] == DIRECT_CHAR)
				&& !((index == 0 || index == 1) && str[index] == LABEL_CHAR))
			return (e_token_label_syntax_fail);
		index++;
	}
	return (FT_SUCCESS);
}

int		check_register(char *str)
{
	if (ft_atoi(str + 1) > REG_NUMBER || ft_atoi(str + 1) < 1)
		return (e_token_register_fail);
	return (FT_SUCCESS);
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
			return (FT_SUCCESS);
		}
		index++;
	}
	return (e_token_instr_invalid);
}
