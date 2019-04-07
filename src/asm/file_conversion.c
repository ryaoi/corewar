/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 12:35:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/07 22:44:42 by jaelee           ###   ########.fr       */
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
	int				index;

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
	{
		ft_putendl("malloc failed.");
		return (NULL);
	}
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

int		label_value(t_line *curr_line, t_line *label_line, t_list *traverse)
{
	int	value;

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
		while (traverse && (&LST_CONT(traverse, t_line) != curr_line))
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
	/*TODO LITTLE -> BIG ENDIAN */
}

int		bc_translation(t_file *file, t_line *line, t_list *traverse, t_op *op)
{
	unsigned char	*bc;
	int				i;
	int				value;
	int				type;

	i = 0;
	bc = line->bytecode;
	while (traverse)
	{
		if (param_getvalue(file->lines, line, &LST_CONT(traverse, t_token)) < 0)
			return (LABEL_NOT_EXIST);
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

static int		conversion(t_file *file, t_line *line)
{
	t_op	*op;
	int 	ret_conv;

	if (!(op = operation_set(line)))
	{
		print_errmsg_conversion(OPERATION_NOT_EXIST, line->str);
		return (FILE_CONVERSION_FAIL);
	}
	if (!line->tokens->next)
	{
		print_errmsg_conversion(PARAMS_NOT_EXIST, line->str);
		return (FILE_CONVERSION_FAIL);
	}
	if ((ret_conv = bc_translation(file, line, line->tokens->next, op)) < 0)
	{
		print_errmsg_conversion(LABEL_NOT_EXIST, line->str);
		return (FILE_CONVERSION_FAIL);
	}
	return (SUCCESS);
}

int		file_conversion(t_file *file)
{
	t_list	*traverse;

	traverse = file->lines;
	while (traverse)
	{
		if (LST_CONT(traverse, t_line).type == T_ASMCODE &&
			LST_CONT(traverse, t_line).tokens)
		{
			if (conversion(file, &LST_CONT(traverse, t_line)) < 0)
				return (FILE_CONVERSION_FAIL);
		}
		/*TODO print translated code*/
		printf("[%s]\n", LST_CONT(traverse, t_line).str);
		printf("bc_length : %zu\n", LST_CONT(traverse, t_line).bytecode_len);
		for (int i=0; i < (int)LST_CONT(traverse, t_line).bytecode_len; i++)
			printf("0x%02x ", LST_CONT(traverse, t_line).bytecode[i]);
		printf("\n-------------------------------------\n");
		traverse = traverse->next;
	}
	return (SUCCESS);
}
