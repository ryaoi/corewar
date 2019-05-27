/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:17:44 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/27 18:11:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned int	token_type_valid(int token_type)
{
	if (token_type == e_name_cmd || token_type == e_comment_cmd
		|| token_type == e_comment)
		return (0);
	return (1);
}

static unsigned int	param_size(int type, int relative)
{
	if (type == e_reg)
		return (REG_INDEX_SIZE);
	else if (type == e_dirlab || type == e_dir)
		return (relative ? DIR_D2_SIZE : DIR_D4_SIZE);
	else if (type == e_indir || type == e_indirlab)
		return (INDIR_SIZE);
	return (0);
}

void				get_bytecode_len(t_line *line)
{
	t_list	*traverse;
	t_op	*op;

	traverse = line->tokens;
	op = ((t_token*)traverse->content)->op;
	if (!line->tokens || !op)
		return ;
	if (!token_type_valid(((t_token*)traverse->content)->type))
		return ;
	line->bytecode_len = 1;
	if (((t_token*)traverse->content)->op->has_ocp == 1)
		line->bytecode_len += 1;
	while (traverse)
	{
		line->bytecode_len += param_size(((t_token*)traverse->content)->type,
								op->relative);
		traverse = traverse->next;
	}
}
