/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:10:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/27 18:12:24 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	if ((converted_type & ~opcode.arg_types[param_id]) > 0)
		return (FT_FAIL);
	return (FT_SUCCESS);
}

int			opcode_cmp(t_line *line)
{
	t_list	*traverse;
	int		instr;
	int		param_id;

	if (!(traverse = line->tokens))
		return (e_param_op_not_exist);
	instr = ((t_token*)traverse->content)->op->opcode - 1;
	if (g_op_tab[instr].arg_num != line->nbr_params)
		return (e_param_nbr_fail);
	if (!(traverse = traverse->next))
		return (e_param_not_exist);
	param_id = 0;
	while (traverse || param_id < g_op_tab[instr].arg_num)
	{
		if (validate_parameters(((t_token*)traverse->content),
				g_op_tab[instr], param_id))
		{
			traverse = traverse->next;
			param_id++;
		}
		else
			return (e_param_not_valid);
	}
	return (FT_SUCCESS);
}

static int	tokenizer(t_line *line)
{
	int	ret_token;
	int	ret_valid;

	if ((ret_token = line_tokenize(line)) < 0)
	{
		print_errmsg_tokenizer(ret_token, line->str);
		return (e_file_parse_fail);
	}
	if ((ret_valid = opcode_cmp(line)) < 0)
	{
		print_errmsg_opcode_cmp(ret_valid, line->str);
		return (e_file_parse_fail);
	}
	if (line->type == e_asmcode)
		get_bytecode_len(line);
	return (FT_SUCCESS);
}

int			file_parse(t_file *file)
{
	t_list	*traverse;

	traverse = file->lines;
	while (traverse)
	{
		if (file->prework_flag != PREWORK_FLAG_ON)
			set_header(file, (t_line*)traverse->content);
		else if (((t_line*)traverse->content)->type == e_unknown)
			((t_line*)traverse->content)->type = e_asmcode;
		if (((t_line*)traverse->content)->type == e_asmcode
			&& (tokenizer(((t_line*)traverse->content)) < 0))
			return (e_file_parse_fail);
		if (((t_line*)traverse->content)->type == e_label)
			remove_label_char(((t_line*)traverse->content)->str);
		traverse = traverse->next;
	}
	if (file->prework_flag != PREWORK_FLAG_ON)
	{
		ft_printf("check the header syntax in %s.\n\n", file->name_s);
		return (e_header_not_found);
	}
	return (FT_SUCCESS);
}
