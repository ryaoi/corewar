/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:23:56 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 22:52:58 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		set_header_index(char *tmp, int *start, int *end)
{
	while (tmp && tmp[*start] && tmp[*start] != '"')
		(*start)++;
	*end = ++(*start);
	while (tmp && tmp[*end] && tmp[*end] != '"')
		(*end)++;
}

static void	set_progname(t_file *file, t_line *line)
{
	int		index;
	char	*tmp;
	int		start;
	int		end;

	index = 0;
	end = 0;
	while (line->str[index] && ft_isspace(line->str[index]))
		index++;
	tmp = line->str + index;
	if (!ft_strncmp(NAME_CMD_STRING, tmp, ft_strlen(NAME_CMD_STRING)))
	{
		start = ft_strlen(NAME_CMD_STRING);
		set_header_index(tmp, &start, &end);
		if (end > start)
		{
			ft_memcpy(file->header.prog_name, line->str + start, end - start);
			file->prework_flag |= 2;
		}
		line->type = T_NAME_CMD;
	}
}

static void	set_how(t_file *file, t_line *line)
{
	int		index;
	char	*tmp;
	int		start;
	int		end;

	index = 0;
	end = 0;
	while (line->str[index] && ft_isspace(line->str[index]))
		index++;
	tmp = line->str + index;
	if (!ft_strncmp(COMMENT_CMD_STRING, tmp, ft_strlen(COMMENT_CMD_STRING)))
	{
		start = ft_strlen(COMMENT_CMD_STRING);
		set_header_index(tmp, &start, &end);
		if (end > start)
		{
			ft_memcpy(file->header.how, line->str + start, end - start);
			file->prework_flag |= 1;
		}
		line->type = T_COMMENT_CMD;
	}
}

void		set_header(t_file *file, t_line *line)
{
	if (~file->prework_flag & 2)
		set_progname(file, line);
	else if (~file->prework_flag & 1)
		set_how(file, line);
}
