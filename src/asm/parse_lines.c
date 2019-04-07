/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:10:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/07 22:46:04 by jaelee           ###   ########.fr       */
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
		return (1);
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

	if (!(len = ft_strlen(str)))
		return (TOKEN_TYPE_FAIL);
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

int		add_token(t_line *line, int token_id, int start, int end)
{
	t_token		token;
	int			len;

	len = end - start;
	init_token(&token);
	if (!(token.str = ft_strsub(line->str, start, len)))
		return (STRSUB_FAIL);
	token.id = token_id;
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

void	get_token(char *str, int *i, int *j)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	*j = *i;
	while (str[*j] && !(ft_isspace(str[*j])) && str[*j] != SEPARATOR_CHAR)
		(*j)++;
}

int		line_tokenize(t_line *line)
{
	size_t	len;
	int		i;
	int		j;
	int		token_id;
	int		ret;

	token_id = 0;
	i = 0;
	j = 0;
	ret = 0;
	len = ft_strlen(line->str);
	while (token_id < 7)
	{
		if (token_id > 5)
			return (TOKEN_TOO_MANY);
		get_token(line->str, &i, &j);
		if ((ret = add_token(line, token_id, i, j)) < 0)
			return (ret);
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
	if ((converted_type & ~opcode.param_types[param_id]) > 0)
		return (FAIL);
	return (SUCCESS);
}

int		opcode_cmp(t_line *line)
{
	t_list	*traverse;
	int		instr;
	int		param_id;

	if (!(traverse = line->tokens))
		return (PARAM_OP_NOT_EXIST);
	instr = LST_CONT(traverse, t_token).op->opcode - 1;
	if (g_op_tab[instr].nbr_params != line->nbr_params)
		return (PARAM_NBR_FAIL);
	if (!(traverse = traverse->next))
		return (PARAM_NOT_EXIST);
	param_id = 0;
	while (traverse || param_id < g_op_tab[instr].nbr_params)
	{
		if (validate_parameters(&LST_CONT(traverse, t_token),
				g_op_tab[instr], param_id))
		{
			traverse = traverse->next;
			param_id++;
		}
		else
			return (PARAM_NOT_VALID);
	}
	return (SUCCESS);
}

static void	set_progname(t_file *file, t_line *line)
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
	file->prework_flag |= 2;
}

static void	set_how(t_file *file, t_line *line)
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
	file->prework_flag |= 1;
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

void	prework(t_file *file, t_line *line)
{
	if (~file->prework_flag & 2)
		set_progname(file, line);
	else if (~file->prework_flag & 1)
		set_how(file, line);
}

static int	token_type_valid(int token_type)
{
	if (token_type == T_NAME_CMD || token_type == T_COMMENT_CMD ||
		token_type == T_COMMENT)
		return (0);
	return (1);
}

static int	param_size(int type, int relative)
{
	if (type == T_REGISTER)
		return (REG_INDEX_SIZE);
	else if (type == T_DIRECT && !relative)
		return (DIR_D4_SIZE);
	else if (type == T_DIRLAB || (type == T_DIRECT && relative))
		return (DIR_D2_SIZE);
	else if (type == T_INDIRECT || type == T_INDIRLAB)
		return (INDIR_SIZE);
	return (0);
}

void	get_bytecode_len(t_line *line)
{
	t_list	*traverse;
	t_op	*op;

	traverse = line->tokens;
	op = LST_CONT(traverse, t_token).op;
	if (!line->tokens || !op)
		return ;
	if (!token_type_valid(LST_CONT(traverse, t_token).type))
		return ;
	line->bytecode_len = 1;
	if (LST_CONT(traverse, t_token).op->ocp == 1)
		line->bytecode_len += 1;
	while (traverse)
	{
		line->bytecode_len += param_size(LST_CONT(traverse, t_token).type,
											op->relative);
		traverse = traverse->next;
	}
}

int		tokenizer(t_line *line)
{
	int	ret_token;
	int	ret_valid;

	if ((ret_token = line_tokenize(line)) < 0)
	{
		print_errmsg_tokenizer(ret_token, line->str);
		return (TOKENIZER_FAIL);
	}
	if ((ret_valid = opcode_cmp(line)) < 0)
	{
		print_errmsg_opcode_cmp(ret_valid, line->str);
		return (OPCODE_CMP_FAIL);
	}
	get_bytecode_len(line);
	return (SUCCESS);
}

int		file_parse(t_file *file)
{
	t_list	*traverse;

	traverse = file->lines;
	while (traverse)
	{
		if (!is_comment(&LST_CONT(traverse, t_line)))
		{
			if (file->prework_flag != PREWORK_FLAG_ON)
				prework(file, &LST_CONT(traverse, t_line));
			if (LST_CONT(traverse, t_line).type == T_UNKNOWN)
				LST_CONT(traverse, t_line).type = T_ASMCODE;
			if (LST_CONT(traverse, t_line).type == T_ASMCODE &&
				(tokenizer(&(LST_CONT(traverse, t_line))) < 0))
				return (FILE_PARSE_FAIL);
			if (LST_CONT(traverse, t_line).type == T_ASMCODE &&
				opcode_cmp(&LST_CONT(traverse, t_line)) < 0)
				return (OPCOMDE_CMP_FAIL);
			if (LST_CONT(traverse, t_line).type == T_LABEL)
				remove_label_char(LST_CONT(traverse, t_line).str);
		}
		traverse = traverse->next;
	}
	return (SUCCESS);
}
