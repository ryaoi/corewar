/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 12:35:50 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/23 19:34:09 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


/* for handling labels in direct and indirect params
	length of the bytecode is necessary
	bytecode_len :
		register = 1
		direct = 4
		direct_label = 2
		indirect = 2 */
t_op	*set_operation(t_line *line)
{
	return (((t_token*)line->tokens->content)->op);
}

int		file_conversion(t_file *file)
{
	t_list	*traverse;
	t_op	*operation;

	traverse = file->lines;
	while (traverse)
	{
		if (LINE->type == T_ASMCODE && LINE->tokens)
			operation = set_operation(LINE);
	}
	return (SUCCESS);
}

