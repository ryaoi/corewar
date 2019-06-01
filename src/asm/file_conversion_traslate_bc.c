/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conversion_traslate_bc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:44:54 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/01 18:29:03 by jaelee           ###   ########.fr       */
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
		while (traverse && ((t_line*)traverse->content) != curr_line)
		{
			traverse = traverse->next;
			if (((t_line*)traverse->content) == curr_line)
				break ;
			value -= ((t_line*)traverse->content)->bytecode_len;
		}
	}
	else if (curr_line->id < label_line->id)
	{
		value += curr_line->bytecode_len;
		while (traverse && (((t_line*)traverse->content) != curr_line))
		{
			value += ((t_line*)traverse->content)->bytecode_len;
			traverse = traverse->prev;
		}
	}
	return (value);
}

int			param_getvalue(t_list *lines, t_line *line, t_token *token)
{
	char	*label;
	t_list	*traverse;

	if (token->type == e_dir || token->type == e_reg)
		token->value = ft_atoi(token->str + 1);
	else if (token->type == e_indir)
		token->value = ft_atoi(token->str);
	else if (token->type == e_dirlab || token->type == e_indirlab)
	{
		label = (token->type == e_dirlab) ? token->str + 2 : token->str + 1;
		traverse = lines;
		while (traverse)
		{
			if (((t_line*)traverse->content)->type == e_label
				&& !ft_strcmp(label, ((t_line*)traverse->content)->str))
			{
				token->value = label_value(line, ((t_line*)traverse->content),
						traverse);
				return (FT_SUCCESS);
			}
			traverse = traverse->next;
		}
		return (e_label_not_exist);
	}
	return (FT_SUCCESS);
}

void		param_trans(unsigned char *bytecode, int size, int *bc_index,
				int value)
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
