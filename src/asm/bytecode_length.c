/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:17:44 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/21 19:47:18 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned int	token_type_valid(int token_type)
{
	if (token_type == e_name_cmd || token_type == e_comment_cmd ||
		token_type == e_comment)
		return (0);
	return (1);
}

static unsigned int	param_size(int type, int relative)
{
	if (type == e_register)
		return (REG_INDEX_SIZE);
	else if (type == e_dirlab || type == e_direct)
		return (relative ? DIR_D2_SIZE : DIR_D4_SIZE);
	else if (type == e_indirect || type == e_indirlab)
		return (INDIR_SIZE);
	return (0);
}

void				get_bytecode_len(t_line *line)
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
