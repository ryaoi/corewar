/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:33:08 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 14:42:46 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		line_is_ws(const char *str)
{
	size_t index;

	index = 0;
	while (str[index] != '\0')
	{
		if (!ft_isspace(str[index]))
			return (0);
		index++;
	}
	return (1);
}

size_t	label_check(char *line)
{
	size_t index;

	index = 0;
	while (line[index] && ft_isspace(line[index]))
		index++;
	while (line[index] && !ft_isspace(line[index]) &&
			line[index] != SEPARATOR_CHAR)
		index++;
	index -= 1;
	if (line[index] == LABEL_CHAR)
		return (index);
	return (0);
}

int		read_error(t_file *file)
{
	if (file->ret == -1)
		return (GNL_FAIL);
	if (file->nbr_line == 0)
		return (CONTENT_EMPTY);
	return (SUCCESS);
}
