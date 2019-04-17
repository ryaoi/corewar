/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conversion_traslate_bc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:44:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 22:16:02 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	label_value(t_line *curr_line, t_line *label_line,
								t_list *traverse)
{
	unsigned int	value;

	value = 0;
	if (curr_line->id > label_line->id)
	{
		while (traverse && &LST_CONT(traverse, t_line) != curr_line)
		{
			traverse = traverse->next;
			if (&LST_CONT(traverse, t_line) == curr_line)
				break ;
			value -= LST_CONT(traverse, t_line).bytecode_len;
		}
	}
	else if (curr_line->id < label_line->id)
	{
		value += curr_line->bytecode_len;
		while (traverse && (&LST_CONT(traverse, t_line) != curr_line))
		{
			value += LST_CONT(traverse, t_line).bytecode_len;
			traverse = traverse->prev;
		}
	}
	return (value);
}

int			param_getvalue(t_list *lines, t_line *line, t_token *token)
{
	char	*label;
	t_list	*traverse;

	if (token->type == T_DIRECT || token->type == T_REGISTER)
		token->value = ft_atoi(token->str + 1);
	else if (token->type == T_INDIRECT)
		token->value = ft_atoi(token->str);
	else if (token->type == T_DIRLAB || token->type == T_INDIRLAB)
	{
		label = token->type == T_DIRLAB ? token->str + 2 : token->str + 1;
		traverse = lines;
		while (traverse)
		{
			if (LST_CONT(traverse, t_line).type == T_LABEL &&
				!ft_strcmp(label, LST_CONT(traverse, t_line).str))
			{
				token->value = label_value(line, &LST_CONT(traverse, t_line),
											traverse);
				return (SUCCESS);
			}
			traverse = traverse->next;
		}
		return (LABEL_NOT_EXIST);
	}
	return (SUCCESS);
}

void		param_trans(unsigned char *bytecode, int size,
							int *bc_index, int value)
{
	if (size == 1)
		bytecode[0] = ((unsigned int)value) % 0x100;
	else if (size == 2)
	{
		bytecode[0] = ((unsigned int)value) / 0x100;
		bytecode[1] = ((unsigned int)value) % 0x100;
	}
	else if (size == 4)
	{
		bytecode[0] = ((unsigned int)value) / (0x100 * 0x100 * 0x100);
		bytecode[1] = ((((unsigned int)value) << 2) >> 2) / (0x100 * 0x100);
		bytecode[2] = ((((unsigned int)value) << 4) >> 4) / 0x100;
		bytecode[3] = ((((unsigned int)value) << 6) >> 6) % 0x100;
	}
	*bc_index = *bc_index + size;
}
