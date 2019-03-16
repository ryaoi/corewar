/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:10:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/16 04:03:54 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* categorize the line type
.name = T_NAME
.comment = T_CMD_COMMENT

different tokens
	- T_LABEL = string + :

	- T_INSTR
		- 1 params instructions
		- 2 params instructions
		- 3 params instructions
	- T_COMMENT
	- parameters
		- T_REGISTRY = r + INTEGER
		- T_DIRECT = % + INTEGER
		- T_DIRLAB = % + : + LABEL
		- T_INDIRECT = INTEGER error ?
		- T_INDIRLAB = : + LABEL
*/

int		is_comment(t_line *line)
{
	int	index;

	index = 0;
	while (line->str && line->str[index] && isspace(line->str[index]))
		index++;
	if (line->str[index] == COMMENT_CHAR)
	{
		line->type = T_COMMENT;
		return (1);
	}
	return (0);
}

void	init_token(t_token *token)
{
	token->id = -1;
	token->str = NULL;
	token->type = T_UNKNOWN;
	token->value = -1;
}

int		is_str_digit(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (0);
		index++;
	}
	return (1);
}

int		check_token_type(t_token *token, char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (token->id == 0)
	{
		if (str[len - 1] == LABEL_CHAR)
			token->type = T_LABEL;
		else
			token->type = T_INSTR;
	}
	else if (str[0] == DIRECT_CHAR)
	{
		if (str[1] == LABEL_CHAR)
			token->type = T_DIRLAB;
		else
			token->type = T_DIRECT;
	}
	else if (str[0] == REGISTER_CHAR)
		token->type = T_REGISTRY;
	else if (str[0] == ':')
		token->type = T_INDIRLAB;
	else if (is_str_digit(str))
		token->type = T_INDIRECT;
	else
		ERROR("no token_type found.", TOKEN_FAIL);
	return (SUCCESS);
}

int		check_parameter(t_token *token, char *str)
{
	int index;
	char *check;

	index = 0;
	check = LABEL_CHARS;
	if (token->type == T_LABEL || T_DIRLAB || T_INDIRLAB)
	{
		while (str[index])
		{
			if (!ft_strchr(check, str[index]) &&
				!(index == 0 && str[index] == DIRECT_CHAR) &&
					!((index == 0 | index == 1) && str[index] == LABEL_CHAR))
				ERROR("wrong syntax of label.", TOKEN_FAIL);
			index++;
		}
		return (SUCCESS);
	}
	else if (token->type = T_REGISTRY)
	{
		if (ft_atoi())
	}
}

int		add_token(t_line *line, int token_id, int start, int end)
{
	t_token		token;
	int			len;

	len = start - end;
	init_token(&token);
	if (!(token.str = ft_strsub(line->str, start, len)))
		ERROR("ft_strsub failed.", TOKEN_FAIL);
	token.id = token_id;
	if (check_token_type(&token, token.str) == TOKEN_FAIL)
		ERROR("token_type error.", TOKEN_FAIL);
	if (check_parameter(&token, token.str) == TOKEN_FAIL)
		ERROR("wrong parameter.", TOKEN_FAIL);
	if (token.type == T_UNKNOWN)
		ERROR("token_type not found.", TOKEN_FAIL);
	if (token.type == T_INSTR && check_instr(&token) == TOKEN_FAIL)
		ERROR("no opcode match found\n", TOKEN_FAIL);
	list_append(&(line->tokens), list_new(&token, sizeof(token)));
	return (SUCCESS);
}

int		tokenize_line(t_line *line)
{
	t_token	*token;
	size_t	len;
	int		start;
	int		end;
	int		token_id;

	token_id = 0;
	len = ft_strlen(line);
	if (!(token = (t_token*)malloc(sizeof(t_token))))
		ERROR("malloc failed.", LINE_FAIL);
	while (line->pos < len)
	{
		if (token_id > 5)
			ERROR("Too many tokens.", LINE_FAIL);
		while (line->str[line->pos] && ft_isspace(line->str))
			line->pos++;
		start = line->pos;
		while (line->str[line->pos] && !(ft_isspace(line->str)) &&
			line->str[line->pos] != SEPARATOR_CHAR)
			line->pos++;
		end = line->pos;
		if (add_token(line, token_id, start, end) == LINE_FAIL)
			ERROR("tokenize failed.", LINE_FAIL);
		token_id++;
	}
	return (SUCCESS);
}

int		check_instrutions(t_line *line)
{
	/* TODO */
	return (SUCCESS);
}



int		parse_file(t_file *file)
{
	t_list	*traverse;

	traverse = file->lines;
	while(traverse)
	{
		if (!is_comment(LINE))
		{
			if (!(file->header.prog_name[0]))
				set_progname(file);
			if (!(file->header.how[0]))
				set_how(file);
			if (LINE->type != T_LABEL)
				LINE->type = T_ASMCODE;
			if (LINE->type == T_ASMCODE && (!(tokenize_line(LINE)) ||
				!(validate_parameters(LINE))))
					file_error("parse failed", file);
		}
		traverse = traverse->next;
	}
}


