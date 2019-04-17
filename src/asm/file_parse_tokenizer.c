/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_tokenizer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:20:06 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/15 19:43:45 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*pullout_token(char *line, int start, int len)
{
	char	*ret;
	int		index;

	if (!(ret = ft_strsub(line, start, len)))
		return (NULL);
	index = 0;
	while (ret[index])
	{
		if (ft_isspace(ret[index]))
			ret[index] = '\0';
		index++;
	}
	return (ret);
}

int			add_token(t_line *line, int token_id, char *str)
{
	t_token		token;

	init_token(&token);
	token.str = str;
	token.id = token_id;
	if (!token.str)
		return (STRSUB_FAIL);
	if (check_token_type(&token, token.str) < 0)
		return (TOKEN_TYPE_FAIL);
	if ((token.type == T_LABEL || token.type == T_DIRLAB
		|| token.type == T_INDIRLAB)
			&& check_label_syntax(token.str) < 0)
		return (TOKEN_LABEL_SYNTAX_FAIL);
	if (token.type == T_REGISTER && check_register(token.str) < 0)
		return (TOKEN_REGISTER_FAIL);
	if (token.type == T_UNKNOWN)
		return (TOKEN_TYPE_UNKNOWN);
	if (token.type == T_INSTR && check_instr(&token, token.str) < 0)
		return (TOKEN_INSTR_INVALID);
	list_append(&(line->tokens), list_new(&token, sizeof(token)));
	return (SUCCESS);
}

void		get_token(char *str, int *i, int *j, int token_id)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	*j = *i;
	if (token_id == 0)
	{
		while (str[*j] && !(ft_isspace(str[*j])) && str[*j] != SEPARATOR_CHAR)
			(*j)++;
	}
	else
	{
		while (str[*j] && str[*j] != SEPARATOR_CHAR)
			(*j)++;
	}
}

int			line_tokenize(t_line *line)
{
	char	*str;
	int		i;
	int		j;
	int		token_id;
	int		ret;

	token_id = 0;
	i = 0;
	j = 0;
	ret = 0;
	str = NULL;
	while (token_id < 7)
	{
		if (token_id > 5)
			return (TOKEN_TOO_MANY);
		get_token(line->str, &i, &j, token_id);
		str = pullout_token(line->str, i, j - i);
		if ((ret = add_token(line, token_id, str)) < 0)
		{
			free(str);
			return (ret);
		}
		i = j + 1;
		if (line->str[i - 1] == '\0')
			break ;
		token_id++;
	}
	line->nbr_params = token_id;
	return (SUCCESS);
}