/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:10:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/21 19:47:34 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
**	categorize the line type
**	.name = T_NAME
**	.comment = T_CMD_COMMENT
**
**	different tokens
**	- e_label = string + :
**
**	- e_instr
**		- 1 params instructions
**		- 2 params instructions
**		- 3 params instructions
**	- e_comment
**	- parameters
**		- T_REGISTRY = r + INTEGER
**		- e_direct = % + INTEGER
**		- e_dirlab = % + : + LABEL
**		- e_indirect = INTEGER error ?
**		- e_indirlab = : + LABEL
*/

static int	validate_parameters(t_token *token, t_op opcode,
											int param_id)
{
	int converted_type;

	converted_type = -1;
	if (token->type == e_dirlab)
		converted_type = T_DIR;
	else
		converted_type = token->type - 10;
	if (converted_type == e_indirlab - 10)
		converted_type = T_IND;
	if ((converted_type & ~opcode.param_types[param_id]) > 0)
		return (FAIL);
	return (SUCCESS);
}

int			opcode_cmp(t_line *line)
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

static int	tokenizer(t_line *line)
{
	int	ret_token;
	int	ret_valid;

	if ((ret_token = line_tokenize(line)) < 0)
	{
		print_errmsg_tokenizer(ret_token, line->str);
		return (FILE_PARSE_FAIL);
	}
	if ((ret_valid = opcode_cmp(line)) < 0)
	{
		print_errmsg_opcode_cmp(ret_valid, line->str);
		return (FILE_PARSE_FAIL);
	}
	if (line->type == e_asmcode)
		get_bytecode_len(line);
	return (SUCCESS);
}

int			file_parse(t_file *file)
{
	t_list	*traverse;

	traverse = file->lines;
	while (traverse)
	{
		if (!(is_comment(&LST_CONT(traverse, t_line))))
		{
			if (file->prework_flag != PREWORK_FLAG_ON)
				set_header(file, &LST_CONT(traverse, t_line));
			else if (LST_CONT(traverse, t_line).type == e_unknown)
				LST_CONT(traverse, t_line).type = e_asmcode;
			if (LST_CONT(traverse, t_line).type == e_asmcode &&
					(tokenizer(&(LST_CONT(traverse, t_line))) < 0))
				return (FILE_PARSE_FAIL);
			if (LST_CONT(traverse, t_line).type == e_label)
				remove_label_char(LST_CONT(traverse, t_line).str);
		}
		traverse = traverse->next;
	}
	if (file->prework_flag != PREWORK_FLAG_ON)
	{
		ft_printf("check the header syntax in %s.\n\n", file->name_s);
		return (HEADER_NOT_FOUND);
	}
	return (SUCCESS);
}
