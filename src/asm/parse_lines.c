/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:10:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/27 18:23:06 by jaelee           ###   ########.fr       */
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

t_op	g_op_tab[17];

int		is_comment(t_line *line)
{
	int	index;

	index = 0;
	while (line->str && line->str[index] && ft_isspace(line->str[index]))
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
	token->op = NULL;
	token->type = T_UNKNOWN;
	token->value = -1;
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
	else if (str[0] == REGISTER_CHAR && is_str_digit(str + 1))
		token->type = T_REGISTER;
	else if (str[0] == LABEL_CHAR)
		token->type = T_INDIRLAB;
	else if (is_str_digit(str))
		token->type = T_INDIRECT;
	else
	{
		/*ft_printf("%s\n", str);*/
		ERROR("no token_type found.", TOKEN_FAIL);
	}
	return (SUCCESS);
}

int		check_parameter(t_token *token, char *str)
{
	int index;

	index = 0;
	if (token->type == T_LABEL || token->type == T_DIRLAB ||
			token->type == T_INDIRLAB)
	{
		while (str[index])
		{
			if (!ft_strchr(LABEL_CHARS, str[index]) &&
				!(index == 0 && str[index] == DIRECT_CHAR) &&
					!((index == 0 | index == 1) && str[index] == LABEL_CHAR))
				ERROR("wrong syntax of label.", TOKEN_FAIL);
			index++;
		}
		return (SUCCESS);
	}
	else if (token->type == T_REGISTER)
	{
		if (ft_atoi(str + 1) > REG_NUMBER)
			ERROR("register number too high.", TOKEN_FAIL);
		return (SUCCESS);
	}
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
				ERROR("malloc failed", TOKEN_FAIL);
			ft_memcpy(token->op, &g_op_tab[index], sizeof(t_op));
			return (SUCCESS);
		}
		index++;
	}
	return (TOKEN_FAIL);
}

int		add_token(t_line *line, int token_id, int start, int end)
{
	t_token		token;
	int			len;

	len = end - start;
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
	if (token.type == T_INSTR && check_instr(&token, token.str) == TOKEN_FAIL)
	{
//		printf("%s\n", line->str + start);
		ERROR("no opcode match found.", TOKEN_FAIL);
	}
	list_append(&(line->tokens), list_new(&token, sizeof(token)));
	return (SUCCESS);
}

int		line_tokenize(t_line *line)
{
	size_t	len;
	int		i;
	int		j;
	int		token_id;

	token_id = 0;
	i = 0;
	j = 0;
	len = ft_strlen(line->str);
	while (token_id < 7)
	{
		if (token_id > 5)
			ERROR("Too many tokens.", LINE_FAIL);
		while (line->str[i] && ft_isspace(line->str[i]))
			i++;
		j = i;
		while (line->str[j] && !(ft_isspace(line->str[j])) &&
			line->str[j] != SEPARATOR_CHAR)
			j++;
		if (add_token(line, token_id, i, j) == LINE_FAIL)
			ERROR("tokenize failed.", LINE_FAIL);
		i = j + 1;
		if (line->str[i - 1] == '\0')
			break ;
		token_id++;
	}
	line->nbr_params = token_id;
	return (SUCCESS);
}

int		validate_parameters(t_token *token, t_op opcode, int param_id)
{
	int converted_type;

	converted_type = -1;
	if (token->type == T_DIRLAB)
		converted_type = T_DIR;
	else
		converted_type = token->type - 10;
	/* filter indirect_label token_type */
	if (converted_type == T_INDIRLAB - 10)
		converted_type = T_IND;
	//printf("t_token->type = %d\nconverted_type = %d\n", token->type, converted_type);
	//printf("param_types[%d] = %d\n-------------------\n", param_id, opcode.param_types[param_id]);
	if ((converted_type & ~opcode.param_types[param_id]) > 0)
		ERROR("not valid parameter_type for particular opcode.", PARAM_FAIL);
	return (SUCCESS);
}

int		validate_opcode_params(t_line *line)
{
	t_list	*traverse;
	int		instr;
	int		param_id;

	traverse = line->tokens;
	if (!(traverse = line->tokens))
		return (LINE_FAIL);
	if (traverse->next == NULL)
		return (LINE_FAIL);
	instr = TOKEN->op->opcode - 1;
//	printf("line type : %d\n", line->type);
//	printf("original : %s\nthe_code : %s\n", g_op_tab[instr].name, line->str);
//	printf("original nbr : %d\nthe_code nbr : %d\n---------------\n", g_op_tab[instr].nbr_params, line->nbr_params);
	if (g_op_tab[instr].nbr_params != line->nbr_params)
		ERROR("wrong number of parameters", LINE_FAIL);
	if (traverse->next == NULL)
		ERROR ("where are the params!!.", LINE_FAIL);
	traverse = traverse->next;
	param_id = 0;
	while (traverse || param_id < g_op_tab[instr].nbr_params)
	{
		if (validate_parameters(TOKEN, g_op_tab[instr], param_id))
		{
			traverse = traverse->next;
			param_id++;
		}
		else
			ERROR("not valid parameters.", LINE_FAIL);
	}
	return (SUCCESS);
}

void	set_progname(t_file *file, t_line *line)
{
	int		index;
	char	*tmp;
	int		start;
	int		end;

	index = 0;
	start = 0;
	end = 0;
	while (line->str[index] && ft_isspace(line->str[index]))
		index++;
	tmp = line->str + index;
	if (!ft_strncmp(NAME_CMD_STRING, tmp, ft_strlen(NAME_CMD_STRING)))
	{
		start = ft_strlen(NAME_CMD_STRING);
		while (tmp && tmp[start] && tmp[start] != '"')
			start++;
		end = ++start;
		while (tmp && tmp[end] && tmp[end] != '"')
			end++;
		if (end > start)
			ft_memcpy(file->header.prog_name, line->str + start, end - start);
		line->type = T_NAME_CMD;
	}
	file->header_flags = ON;
}

void	set_how(t_file *file, t_line *line)
{
	int		index;
	char	*tmp;
	int		start;
	int		end;

	index = 0;
	start = 0;
	end = 0;
	while (line->str[index] && ft_isspace(line->str[index]))
		index++;
	tmp = line->str + index;
	if (!ft_strncmp(COMMENT_CMD_STRING, tmp, ft_strlen(COMMENT_CMD_STRING)))
	{
		start = ft_strlen(COMMENT_CMD_STRING);
		while (tmp && tmp[start] && tmp[start] != '"')
			start++;
		end = ++start;
		while (tmp && tmp[end] && tmp[end] != '"')
			end++;
		if (end > start)
			ft_memcpy(file->header.how, line->str + start, end - start);
		line->type = T_COMMENT_CMD;
	}
}
void	bytecode_len(t_line *line)
{
	t_list	*traverse;
	t_op	*operation;

	traverse = line->tokens;
	operation = TOKEN->op;
	if (!line->tokens || !operation)
		return ;
	if (TOKEN->type == T_NAME_CMD || TOKEN->type == T_COMMENT_CMD ||
		TOKEN->type == T_COMMENT)
		return ;
	line->bytecode_len = 1;
	if (TOKEN->op->ocp == 1)
		line->bytecode_len += 1;
	while (traverse)
	{
		if (TOKEN->type == T_REGISTER)
			line->bytecode_len += REGISTER_INDEX_SIZE;
		else if (TOKEN->type == T_DIRECT && !(operation->relative))
			line->bytecode_len += DIRECT_D4_SIZE;
		else if (TOKEN->type == T_DIRLAB ||
					(TOKEN->type == T_DIRECT && operation->relative))
			line->bytecode_len += DIRECT_D2_SIZE;
		else if (TOKEN->type == T_INDIRECT || TOKEN->type == T_INDIRLAB)
			line->bytecode_len += INDIRECT_SIZE;
		traverse = traverse->next;
	}
}

void	remove_label_char(char *str)
{
	int index;
	char	*tmp;

	tmp = NULL;
	index = 0;
	while (str && str[index])
	{
		if (str[index] == LABEL_CHAR)
			str[index] = '\0';
		index++;
	}
}

int		file_parse(t_file *file)
{
	t_list	*traverse;

	traverse = file->lines;
	while(traverse)
	{
		if (!is_comment(LINE))
		{
			if (!(file->header.prog_name[0]))
				set_progname(file, LINE);
			if (!(file->header.how[0]))
				set_how(file, LINE);
			if (LINE->type == T_UNKNOWN)
				LINE->type = T_ASMCODE;
			if (LINE->type == T_ASMCODE && (!(line_tokenize(LINE)) ||
				!(validate_opcode_params(LINE))))
					file_error("parse failed.", file);
			if (LINE->type == T_ASMCODE)
				bytecode_len(LINE);
			else if (LINE->type == T_LABEL)
				remove_label_char(LINE->str); /*TODO needs to code it */
		}
		traverse = traverse->next;
	}
	return (SUCCESS);
}
