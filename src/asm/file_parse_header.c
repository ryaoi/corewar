/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:23:56 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 15:38:54 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	set_progname(t_file *file, t_line *line)
{
	int		index;
	char	*tmp;
	int		start;
	int		end;

	index = 0;
	start = 0;
	end = 0;
	while (line->str[index] && ft_isspace(line->str[index]))
		index++;
	tmp = line->str + index;
	if (!ft_strncmp(NAME_CMD_STRING, tmp, ft_strlen(NAME_CMD_STRING)))
	{
		start = ft_strlen(NAME_CMD_STRING);
		while (tmp && tmp[start] && tmp[start] != '"')
			start++;
		end = ++start;
		while (tmp && tmp[end] && tmp[end] != '"')
			end++;
		if (end > start)
			ft_memcpy(file->header.prog_name, line->str + start, end - start);
		line->type = T_NAME_CMD;
	}
	file->prework_flag |= 2;
}

static void	set_how(t_file *file, t_line *line)
{
	int		index;
	char	*tmp;
	int		start;
	int		end;

	index = 0;
	start = 0;
	end = 0;
	while (line->str[index] && ft_isspace(line->str[index]))
		index++;
	tmp = line->str + index;
	if (!ft_strncmp(COMMENT_CMD_STRING, tmp, ft_strlen(COMMENT_CMD_STRING)))
	{
		start = ft_strlen(COMMENT_CMD_STRING);
		while (tmp && tmp[start] && tmp[start] != '"')
			start++;
		end = ++start;
		while (tmp && tmp[end] && tmp[end] != '"')
			end++;
		if (end > start)
			ft_memcpy(file->header.how, line->str + start, end - start);
		line->type = T_COMMENT_CMD;
	}
	file->prework_flag |= 1;
}

void		set_header(t_file *file, t_line *line)
{
	if (~file->prework_flag & 2)
		set_progname(file, line);
	else if (~file->prework_flag & 1)
		set_how(file, line);
}
