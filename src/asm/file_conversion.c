/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 12:35:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/24 18:56:56 by jaelee           ###   ########.fr       */
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
		return (0);
	token = (t_token*)line->tokens->content;
	if (token->op)
	{
		line->bytecode[0] = token->op->opcode;
		if (token->op->ocp)
			ocp_set(line->tokens->next, line->bytecode);
		//printf("%#4x | %#4x\n-------------\n", line->bytecode[0], line->bytecode[1]);
		return (((t_token*)line->tokens->content)->op);
	}
	return (NULL);
}

void	get_label_value(void)
{
	return ;
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
				get_label_value(); /*TODO fuck.... dunno how direct and indirect labels  are different..*/
				return (SUCCESS);
			}
			traverse = traverse->next;
		}
		ERROR("noooooooo label doesn't exist.", 0);
	}
	return (SUCCESS);
}

void	param_translate(size_t size) /*TODO */
{
	(void)size;
	return ;
}

int		bytecode_conversion(t_file *file, t_line *line, t_op *op)
{
	t_list	*traverse;

	int		bc_index;

	bc_index = 0;
	traverse = line->tokens->next;
	while (traverse)
	{
		if (!(param_getvalue(file->lines, line, ((t_token*)traverse->content))))
			ERROR("param_getvalue failed.", 0);
		if (((t_token*)traverse->content)->type == T_INDIRECT ||
				((t_token*)traverse->content)->type == T_INDIRLAB)
			param_translate(INDIRECT_SIZE); /* TODO */
		else if (((t_token*)traverse->content)->type == T_DIRLAB ||
					(((t_token*)traverse->content)->type == T_DIRECT &&
						op->relative))
			param_translate(DIRECT_D2_SIZE);
		else if (((t_token*)traverse->content)->type == T_DIRECT &&
					!(op->relative))
			param_translate(DIRECT_D4_SIZE);
		else if (((t_token*)traverse->content)->type == T_REGISTER)
			param_translate(REGISTER_INDEX_SIZE);
		printf("param value : %d\n", ((t_token*)traverse->content)->value);
		traverse = traverse->next;
	}
	return 1;
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

