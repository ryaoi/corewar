/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 12:35:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/27 12:18:22 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


/* for handling labels in direct and indirect params
	length of the bytecode is necessary
	bytecode_len :
		register = 1
		direct = 4
		direct_label = 2
		indirect = 2
01 Register, followed by a byte (the register number)
10 Direct, followed by DIR_SIZE bytes (the direct value)
11 Indirect, followed by IND_SIZE bytes (the value of the indirection) */

static void	ocp_set(t_list *tokens, unsigned char *bytecode)
{
	unsigned int	ocp;
	int	index;

	ocp = 0;
	index = 0;

	while (tokens)
	{
		if (((t_token*)tokens->content)->type == T_REGISTER)
			ocp |= 1 << (6 - index);
		else if (((t_token*)tokens->content)->type == T_DIRECT ||
					((t_token*)tokens->content)->type == T_DIRLAB)
			ocp |= 2 << (6 - index);
		else if (((t_token*)tokens->content)->type == T_INDIRECT ||
					((t_token*)tokens->content)->type == T_INDIRLAB)
			ocp |= 3 << (6 - index);
		tokens = tokens->next;
		index += 2;
	}
	bytecode[1] = ocp;
//	printf("%d | %d\n----------------\n", bytecode[0], bytecode[1]);
}

t_op	*operation_set(t_line *line)
{
	t_token	*token;

	if (!(line->bytecode = ft_memalloc(sizeof(char) * (line->bytecode_len + 1))))
		ERROR("malloc failed.", 0);
	token = (t_token*)line->tokens->content;
	if (token->op)
	{
		line->bytecode[0] = token->op->opcode;
		if (token->op->ocp)
			ocp_set(line->tokens->next, line->bytecode);
		//printf("0x%2x | 0x%2x\n-------------\n", line->bytecode[0], line->bytecode[1]);
		return (((t_token*)line->tokens->content)->op);
	}
	return (NULL);
}

int		get_label_value(t_line *curr_line, t_line *label_line, t_list *traverse)
{
	int	value;

	value = 0;
	if (curr_line->id > label_line->id)
	{
		while (traverse && (((t_line*)traverse->content) != curr_line))
		{
			value -= ((t_line*)traverse->content)->bytecode_len;
			traverse = traverse->prev;
		}
	}
	else if (curr_line->id < label_line->id)
	{
		while (traverse && (((t_line*)traverse->content) != curr_line))
		{
			value += ((t_line*)traverse->content)->bytecode_len;
			traverse = traverse->next;
		}
	}
	return (value);
}

int		param_getvalue(t_list *lines, t_line *line, t_token *token)
{
	char	*label;
	t_list	*traverse;
	(void)line;

	label = NULL;
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
			if (((t_line*)traverse->content)->type == T_LABEL &&
				!ft_strcmp(label, ((t_line*)traverse->content)->str))
			{
				token->value = get_label_value(line, ((t_line*)traverse->content), traverse); /*TODO fuck.... dunno how direct and indirect labels  are different..*/
				return (SUCCESS);
			}
			traverse = traverse->next;
		}
		ERROR("noooooooo label doesn't exist.", 0);
	}
	return (SUCCESS);
}

void	param_translate(unsigned char *bytecode, size_t size, int *bc_index, int value) /*TODO */
{
	if (size == 1)
		bytecode[0] = (unsigned int)value % 0x100;
	else if (size == 2)
	{
		bytecode[0] = (unsigned int)value / 0x100;
		bytecode[1] = (unsigned int)value % 0x100;
	}
	else if (size == 4)
	{
		bytecode[0] = (unsigned int)value / (0x100 * 0x100 * 0x100);
		bytecode[1] = (unsigned int)value /*- 2 biggest digits*/ / (0x100 * 0x100);
		bytecode[2] = (unsigned int)value /*- 2 biggest digits*/ / (0x100);
		bytecode[3] = (unsigned int)value /*- 2 biggest digits*/ % 0x100;
	}
	bc_index = bc_index + size;
}

int		bytecode_conversion(t_file *file, t_line *line, t_op *op)
{
	t_list			*traverse;
	int				bc_index;
	unsigned char	*bytecode;

	bc_index = 0;
	traverse = line->tokens->next;
	bytecode = line->bytecode;
	while (traverse)
	{
		if (!(param_getvalue(file->lines, line, ((t_token*)traverse->content))))
			ERROR("param_getvalue failed.", 0);

		if (((t_token*)traverse->content)->type == T_INDIRECT ||
				((t_token*)traverse->content)->type == T_INDIRLAB)
			param_translate(&bytecode[1 + op->ocp + bc_index], INDIRECT_SIZE, &bc_index,
				((t_token*)traverse->content)->value); /* TODO */

		else if (((t_token*)traverse->content)->type == T_DIRLAB ||
					(((t_token*)traverse->content)->type == T_DIRECT &&
						op->relative))
			param_translate(&bytecode[1 + op->ocp + bc_index], DIRECT_D2_SIZE, &bc_index,
				((t_token*)traverse->content)->value);

		else if (((t_token*)traverse->content)->type == T_DIRECT &&
					!(op->relative))
			param_translate(&bytecode[1 + op->ocp + bc_index], DIRECT_D4_SIZE, &bc_index,
				((t_token*)traverse->content)->value);

		else if (((t_token*)traverse->content)->type == T_REGISTER)
			param_translate(&bytecode[1 + op->ocp + bc_index], REGISTER_INDEX_SIZE, &bc_index,
				((t_token*)traverse->content)->value);

		printf("param value : %d\n", ((t_token*)traverse->content)->value);
		traverse = traverse->next;
	}
	return (SUCCESS);
}

int		file_conversion(t_file *file)
{
	t_list	*traverse;
	t_op	*operation;

	traverse = file->lines;
	while (traverse)
	{
		if (LINE->type == T_ASMCODE && LINE->tokens)
		{
			if (!(operation = operation_set(LINE)))
				ERROR("operation doesn't exist.", CONVERSION_FAIL);
			if (!(LINE->tokens->next))
				ERROR("no parameters found.", CONVERSION_FAIL);
			if (!bytecode_conversion(file, LINE, operation))
				ERROR("conversion failed.", CONVERSION_FAIL);
		}
		traverse = traverse->next;
	}
	return (SUCCESS);
}

