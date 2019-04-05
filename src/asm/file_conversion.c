/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 12:35:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/05 18:10:22 by jaelee           ###   ########.fr       */
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
ocp :
01 Register, followed by a byte (the register number)
10 Direct, followed by DIR_SIZE bytes (the direct value)
11 Indirect, followed by IND_SIZE bytes (the value of the indirection) */

static void	ocp_set(t_list *tokens, unsigned char *bytecode)
{
	unsigned int	ocp;
	t_list			*traverse;
	int	index;

	ocp = 0;
	index = 0;
	traverse = tokens;
	while (traverse)
	{
		if (LST_CONT(traverse, t_token).type == T_REGISTER)
			ocp |= 1 << (6 - index);
		else if (LST_CONT(traverse, t_token).type == T_DIRECT ||
				LST_CONT(traverse, t_token).type == T_DIRLAB)
			ocp |= 2 << (6 - index);
		else if (LST_CONT(traverse, t_token).type == T_INDIRECT ||
					LST_CONT(traverse, t_token).type == T_INDIRLAB)
			ocp |= 3 << (6 - index);
		traverse = traverse->next;
		index += 2;
	}
	bytecode[1] = ocp;
}

t_op	*operation_set(t_line *line)
{
	t_token	*token;

	if (!(line->bytecode = ft_memalloc(sizeof(char) * (line->bytecode_len))))
		ERROR("malloc failed.", NULL);
	token = (t_token*)line->tokens->content;
	if (token->op)
	{
		line->bytecode[0] = token->op->opcode;
		if (token->op->ocp)
			ocp_set(line->tokens->next, line->bytecode);
		return (((t_token*)line->tokens->content)->op);
	}
	return (NULL);
}

int		get_label_value(t_line *curr_line, t_line *label_line, t_list *traverse)
{
	int	value;
	/*TODO offset reference is from beginning of instr->label_line OR param->label_line */
	value = 0;
	if (curr_line->id > label_line->id)
	{
		while (traverse && (((t_line*)traverse->content) != curr_line))
		{
			traverse = traverse->next;
			if ((((t_line*)traverse->content) == curr_line))
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

int		param_getvalue(t_list *lines, t_line *line, t_token *token)
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
				token->value = get_label_value(line,
					&LST_CONT(traverse, t_line), traverse);
				return (SUCCESS);
			}
			traverse = traverse->next;
		}
		ERROR("noooooooo label doesn't exist.", 0);
	}
	return (SUCCESS);
}

void	param_trans(unsigned char *bytecode, int size,
							int *bc_index, int value)
{
	/*TODO check if 'unsigned int' casting is OK */
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

int		bytecode_conversion(t_file *file, t_line *line, t_op *op)
{
	t_list			*traverse;
	int				i;
	unsigned char	*bc;
	int				value;
	int				type;

	i = 0;
	traverse = line->tokens->next;
	bc = line->bytecode;
	while (traverse)
	{
		if (!(param_getvalue(file->lines, line, &LST_CONT(traverse, t_token))))
			ERROR("param_getvalue failed.", 0);
		value = LST_CONT(traverse, t_token).value;
		type = LST_CONT(traverse, t_token).type;
		if (type == T_INDIRECT || type == T_INDIRLAB)
			param_trans(&bc[1 + op->ocp + i], INDIR_SIZE, &i, value);
		else if (type == T_DIRLAB || (type == T_DIRECT && op->relative))
			param_trans(&bc[1 + op->ocp + i], DIR_D2_SIZE, &i, value);
		else if (type == T_DIRECT && !(op->relative))
			param_trans(&bc[1 + op->ocp + i], DIR_D4_SIZE, &i, value);
		else if (type == T_REGISTER)
			param_trans(&bc[1 + op->ocp + i], REG_INDEX_SIZE, &i, value);
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
		if (LST_CONT(traverse, t_line).type == T_ASMCODE &&
			LST_CONT(traverse, t_line).tokens)
		{
			if (!(operation = operation_set(&LST_CONT(traverse, t_line))))
				ERROR("operation doesn't exist.", CONVERSION_FAIL);
			if (!(LST_CONT(traverse, t_line).tokens->next))
				ERROR("no parameters found.", CONVERSION_FAIL);
			if (!bytecode_conversion(file, &LST_CONT(traverse, t_line), operation))
				ERROR("conversion failed.", CONVERSION_FAIL);
		}
		/*TODO print translated code*/
		printf("%s\n", LST_CONT(traverse, t_line).str);
		for (int i=0; i < (int)LST_CONT(traverse, t_line).bytecode_len; i++)
			printf("0x%02x ", LST_CONT(traverse, t_line).bytecode[i]);
		printf("\n-------------------------------------\n");
		traverse = traverse->next;
	}
	return (SUCCESS);
}
