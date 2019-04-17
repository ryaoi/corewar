/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode_length.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:17:44 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 16:28:15 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned int	token_type_valid(int token_type)
{
	if (token_type == T_NAME_CMD || token_type == T_COMMENT_CMD ||
		token_type == T_COMMENT)
		return (0);
	return (1);
}

static unsigned int	param_size(int type, int relative)
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
