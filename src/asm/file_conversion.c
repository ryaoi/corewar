/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 12:35:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/04 16:04:13 by pmorgan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				bc_translation(t_file *file, t_line *line, t_list *traverse,
								t_op *op)
{
	unsigned char	*bc;
	int				i;
	int				value;
	int				type;

	i = 0;
	bc = line->bytecode;
	while (traverse)
	{
		if (param_getvalue(file->lines, line,
				((t_token*)traverse->content)) < 0)
			return (e_label_not_exist);
		value = ((t_token*)traverse->content)->value;
		type = ((t_token*)traverse->content)->type;
		if (type == e_indir || type == e_indirlab)
			param_trans(&bc[1 + op->has_ocp + i], INDIR_SIZE, &i, value);
		else if (type == e_dirlab || type == e_dir)
			param_trans(&bc[1 + op->has_ocp + i],
				op->relative ? DIR_D2_SIZE : DIR_D4_SIZE, &i, value);
		else if (type == e_reg)
			param_trans(&bc[1 + op->has_ocp + i], REG_INDEX_SIZE, &i, value);
		traverse = traverse->next;
	}
	return (FT_SUCCESS);
}

static void		ocp_set(t_list *tokens, unsigned char *bytecode)
{
	unsigned int	ocp;
	t_list			*traverse;
	int				index;

	ocp = 0;
	index = 0;
	traverse = tokens;
	while (traverse)
	{
		if (((t_token*)traverse->content)->type == e_reg)
			ocp |= 1 << (6 - index);
		else if (((t_token*)traverse->content)->type == e_dir
			|| ((t_token*)traverse->content)->type == e_dirlab)
			ocp |= 2 << (6 - index);
		else if (((t_token*)traverse->content)->type == e_indir
			|| ((t_token*)traverse->content)->type == e_indirlab)
			ocp |= 3 << (6 - index);
		traverse = traverse->next;
		index += 2;
	}
	bytecode[1] = ocp;
}

t_op			*operation_set(t_line *line)
{
	t_token	*token;

	if (!(line->bytecode = ft_memalloc(sizeof(char) * (line->bytecode_len))))
	{
		ft_putendl("malloc failed.");
		return (NULL);
	}
	token = (t_token*)line->tokens->content;
	if (token->op)
	{
		line->bytecode[0] = token->op->opcode;
		if (token->op->has_ocp)
			ocp_set(line->tokens->next, line->bytecode);
		return (((t_token*)line->tokens->content)->op);
	}
	return (NULL);
}

static int		conversion(t_file *file, t_line *line)
{
	t_op	*op;
	int		ret_conv;

	if (!(op = operation_set(line)))
	{
		print_errmsg_conversion(e_operation_not_exist, line->str);
		return (e_file_conversion_fail);
	}
	if (!line->tokens->next)
	{
		print_errmsg_conversion(e_conv_params_not_exist, line->str);
		return (e_file_conversion_fail);
	}
	if ((ret_conv = bc_translation(file, line, line->tokens->next, op)) < 0)
	{
		print_errmsg_conversion(e_label_not_exist, line->str);
		return (e_file_conversion_fail);
	}
	return (FT_SUCCESS);
}

int				file_conversion(t_file *file)
{
	t_list	*traverse;

	traverse = file->lines;
	while (traverse)
	{
		if (((t_line*)traverse->content)->type == e_asmcode
			&& ((t_line*)traverse->content)->tokens)
		{
			if (conversion(file, ((t_line*)traverse->content)) < 0)
				return (e_file_conversion_fail);
		}
		traverse = traverse->next;
	}
	return (FT_SUCCESS);
}
