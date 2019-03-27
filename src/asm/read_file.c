/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:17:00 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/27 18:22:12 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "get_next_line.h"

int		is_whitespaces_line(const char *str)
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

static size_t	label_check(char *line)
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

int		line_create(t_file *file, char *line, size_t nbr_lines, int line_type)
{
	t_line new_line;

	new_line.tokens = NULL;
	if (!(new_line.str = ft_strtrim(line)))
		file_error("ft_strtrim failed", file);
	new_line.nbr_params = 0;
	new_line.id = nbr_lines;
	new_line.type = line_type;
	new_line.pos = 0;
	new_line.bytecode = NULL;
	new_line.bytecode_len = 0;
	if (new_line.str && *(new_line.str))
		list_append(&(file->lines), list_new(&new_line, sizeof(new_line)));
	return (SUCCESS);
}

int		line_add(t_file *file, char *line, size_t *nbr_lines, size_t label_pos)
{
	size_t	len;

	len = ft_strlen(line);
	if (label_pos)
	{
		/* parse label : && treat label: instructions format */
		line[label_pos + 1] = '\0';
		line_create(file, line, *nbr_lines, T_LABEL);
		line[label_pos + 1] = ' ';
		/*parse asm code */
		if (len > label_pos + 1 && !is_whitespaces_line((&line[label_pos + 2])))
			line_create(file, line + label_pos + 2, ++(*nbr_lines), T_UNKNOWN);
	}
	else
		line_create(file, line, *nbr_lines, T_UNKNOWN);
	free(line);
	return (1);
}

void	file_read(t_file *file)
{
	char	*line;
	size_t	nbr_lines;

	nbr_lines = 0;
	line = NULL;
	while ((file->ret = get_next_line(file->fd_s, &line)) > 0)
	{
		if (line && (line[0] =='\0' || is_whitespaces_line(line)))
		{
			free(line);
			continue ;
		}
		if (line_add(file, line, &nbr_lines, label_check(line)) == ASM_FAIL)
		{
			free(line);
			file_error("syntax error in line.", file);
		}
		nbr_lines++;
	}
	free(line);
	if (file->ret == -1)
		file_error("get_next_line failed.", file);
	else if ((file->nbr_line = nbr_lines) == 0)
		file_error("no instructions.", file);
	/* print lines
	int i = 0;
	t_list *traverse;
	traverse = file->lines;
	while (traverse != NULL)
	{
		printf("line[%d] = %s\n", i, ((t_line*)traverse->content)->str);
		traverse = traverse->next;
		i++;
	}*/
}
