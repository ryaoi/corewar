/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:17:00 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 15:39:19 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

int		line_create(t_file *file, char *line, int line_type)
{
	t_line new_line;

	new_line.tokens = NULL;
	if (!(new_line.str = ft_strtrim(line)))
	{
		ft_putendl("ft_strtrim failed.");
		return (LINE_CREATE_FAIL);
	}
	new_line.nbr_params = 0;
	new_line.id = file->nbr_line;
	new_line.type = line_type;
	new_line.pos = 0;
	new_line.bytecode = NULL;
	new_line.bytecode_len = 0;
	if (new_line.str && *(new_line.str))
		list_append(&(file->lines), list_new(&new_line, sizeof(new_line)));
	return (SUCCESS);
}

int		line_add(t_file *file, char *line, size_t label_pos)
{
	size_t	len;

	len = ft_strlen(line);
	if (label_pos)
	{
		line[label_pos + 1] = '\0';
		if (line_create(file, line, T_LABEL) < 0)
			return (LINE_CREATE_FAIL);
		line[label_pos + 1] = ' ';
		if (len > label_pos + 1 && !line_is_ws((&line[label_pos + 2])))
		{
			file->nbr_line++;
			if (line_create(file, line + label_pos + 2, T_UNKNOWN) < 0)
				return (LINE_CREATE_FAIL);
		}
	}
	else
	{
		if (line_create(file, line, T_UNKNOWN) < 0)
			return (LINE_CREATE_FAIL);
	}
	free(line);
	return (SUCCESS);
}

int		handle_comment(t_file *file, char **line)
{
	int		index;
	char	*tmp;

	index = 0;
	while (*line && (*line)[index] != COMMENT_CHAR)
		index++;
	if (line_create(file, &((*line)[index]), T_COMMENT) < 0)
	{
		free(*line);
		return (LINE_CREATE_FAIL);
	}
	if (index > 0)
	{
		file->nbr_line++;
		if (!(tmp = ft_strsub(*line, 0, index)))
		{
			ft_putendl("ft_strsub() failed.");
			return (HANDLE_CMT_FAIL);
		}
		free(*line);
		*line = tmp;
	}
	free(*line);
	return (SUCCESS);
}

int		file_read(t_file *file)
{
	char	*line;

	line = NULL;
	while ((file->ret = get_next_line(file->fd_s, &line)) > 0)
	{
		if (line && (line[0] == '\0' || line_is_ws(line)))
		{
			free(line);
			continue ;
		}
		if (ft_strchr(line, COMMENT_CHAR))
			if (handle_comment(file, &line) < 0)
				return (HANDLE_CMT_FAIL);
		if (line && line_add(file, line, label_check(line)) < 0)
		{
			free(line);
			return (LINE_CREATE_FAIL);
		}
		file->nbr_line++;
	}
	free(line);
	if (file->ret == -1 || file->nbr_line == 0)
		return (read_error(file));
	return (SUCCESS);
}
