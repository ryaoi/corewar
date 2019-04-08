/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 12:35:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 17:45:42 by jaelee           ###   ########.fr       */
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
		if (token->op->ocp)
			ocp_set(line->tokens->next, line->bytecode);
		return (((t_token*)line->tokens->content)->op);
	}
	return (NULL);
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

int				file_conversion(t_file *file)
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
		printf("asm: %s\n", LST_CONT(traverse, t_line).str);
		printf("line id: %zu\n", LST_CONT(traverse, t_line).id);
		printf("bc_length : %u\n", LST_CONT(traverse, t_line).bytecode_len);
		for (int i=0; i < (int)LST_CONT(traverse, t_line).bytecode_len; i++)
			printf("0x%02x ", LST_CONT(traverse, t_line).bytecode[i]);
		printf("\n-------------------------------------\n");
		traverse = traverse->next;
	}
	return (SUCCESS);
}
