/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:17:00 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/01 18:28:29 by jaelee           ###   ########.fr       */
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
		return (e_line_create_fail);
	}
	if (new_line.str && new_line.str[0] == '\0')
	{
		free(new_line.str);
		ft_printf("at %s, ft_strtrim returned empty string!.\n", file->name_s);
		return (e_line_create_fail);
	}
	new_line.nbr_params = 0;
	new_line.id = file->nbr_line;
	new_line.type = line_type;
	new_line.pos = 0;
	new_line.bytecode = NULL;
	new_line.bytecode_len = 0;
	if (new_line.str && *(new_line.str))
		list_append(&(file->lines), list_new(&new_line, sizeof(new_line)));
	return (FT_SUCCESS);
}

int		line_add(t_file *file, char *line, size_t label_pos)
{
	size_t	len;

	len = ft_strlen(line);
	if (label_pos)
	{
		line[label_pos + 1] = '\0';
		if (line_create(file, line, e_label) < 0)
			return (e_line_create_fail);
		line[label_pos + 1] = ' ';
		if (len > label_pos + 1 && !line_is_ws((&line[label_pos + 2])))
		{
			file->nbr_line++;
			if (line_create(file, line + label_pos + 2, e_unknown) < 0)
				return (e_line_create_fail);
		}
	}
	else if (line_create(file, line, e_unknown) < 0)
		return (e_line_create_fail);
	free(line);
	return (FT_SUCCESS);
}

void	handle_comment(char *line)
{
	int		index;
	char	*tmp;

	index = 0;
	while (line[index] && ft_isspace(line[index]))
		index++;
	tmp = line + index;
	if (!ft_strncmp(NAME_CMD_STRING, tmp, ft_strlen(NAME_CMD_STRING))
		|| !ft_strncmp(COMMENT_CMD_STRING, tmp, ft_strlen(COMMENT_CMD_STRING)))
		return ;
	else
	{
		index = 0;
		while (line[index] && line[index] != COMMENT_CHAR)
			index++;
		line[index] = '\0';
	}
}

int		file_read(t_file *file)
{
	char	*line;

	line = NULL;
	while ((file->ret = get_next_line(file->fd_s, &line)) > 0)
	{
		if (line && ft_strchr(line, COMMENT_CHAR))
			handle_comment(line);
		if (line && (line[0] == '\0' || line_is_ws(line)))
		{
			free(line);
			continue ;
		}
		if (line && line_add(file, line, label_check(line)) < 0)
		{
			free(line);
			return (e_line_create_fail);
		}
		file->nbr_line++;
	}
	free(line);
	if (file->ret == -1 || file->nbr_line == 0)
		return (read_error(file));
	return (FT_SUCCESS);
}
