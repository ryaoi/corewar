/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_tokenizer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:20:06 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/27 15:18:44 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*pullout_token(char *line, int *start, int end)
{
	char	*ret;
	int		index;
	int		len;

	len = end - *start;
	if (!(ret = ft_strsub(line, *start, len)))
		return (NULL);
	index = 0;
	while (ret[index])
	{
		if (ft_isspace(ret[index]))
			ret[index] = '\0';
		index++;
	}
	*start = end + 1;
	return (ret);
}

int			add_token(t_line *line, int token_id, char *str)
{
	t_token		token;

	init_token(&token);
	token.str = str;
	token.id = token_id;
	if (!token.str)
		return (e_strsub_fail);
	if (check_token_type(&token, token.str) < 0)
		return (e_token_type_fail);
	if ((token.type == e_label || token.type == e_dirlab
		|| token.type == e_indirlab)
			&& check_label_syntax(token.str) < 0)
		return (e_token_label_syntax_fail);
	if (token.type == e_reg && check_register(token.str) < 0)
		return (e_token_register_fail);
	if (token.type == e_unknown)
		return (e_token_type_unknwon);
	if (token.type == e_instr && check_instr(&token, token.str) < 0)
		return (e_token_instr_invalid);
	list_append(&(line->tokens), list_new(&token, sizeof(token)));
	return (FT_SUCCESS);
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
	int		start;
	int		end;
	int		token_id;
	int		ret;

	token_id = 0;
	start = 0;
	end = 0;
	while (token_id < 7 && line->str[end] != '\0')
	{
		if (token_id > 5)
			return (e_token_too_many);
		get_token(line->str, &start, &end, token_id);
		str = pullout_token(line->str, &start, end);
		if ((ret = add_token(line, token_id, str)) < 0)
		{
			free(str);
			return (ret);
		}
		token_id++;
	}
	line->nbr_params = token_id - 1;
	return (FT_SUCCESS);
}
