/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:12:52 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 15:39:34 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <sys/stat.h>
#include <fcntl.h>

void	file_init(t_file *file)
{
	file->lines = NULL;
	file->nbr_line = 0;
	file->name_s = NULL;
	file->name_cor = NULL;
	file->fd_s = -1;
	file->fd_cor = -1;
	file->prework_flag = 0;
	ft_bzero(&(file->header.prog_name[0]), PROG_NAME_LENGTH + 1);
	ft_bzero(&(file->header.how[0]), COMMENT_LENGTH + 1);
}

int		file_name_check(const char *filename, t_file *file)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(filename);
	if (len < 3 || filename[len - 2] != '.' || filename[len - 1] != 's')
		return (DOT_S_ERROR);
	if ((file->fd_s = open(filename, O_RDONLY)) == -1)
		return (OPEN_FILE_ERROR);
	if (!(file->name_s = ft_strdup(filename)))
		return (STRDUP_FAIL);
	if (!(tmp = (char*)ft_strsub(filename, 0, len - 2)))
		return (STRNDUP_FAIL);
	if (!(file->name_cor = ft_strjoin(tmp, ".cor")))
	{
		free(tmp);
		return (STRJOIN_FAIL);
	}
	free(tmp);
	return (SUCCESS);
}

int		argv_check(int argc, char **argv, int *option)
{
	if (argc == 1)
	{
		ft_putendl("no file identified. Usage: ./asm [filename.s] [-p]");
		return (FILE_ERROR);
	}
	else if (argc > 1)
	{
		if (!ft_strcmp(argv[1], "-p"))
			*option = ON;
	}
	return (SUCCESS);
}

void	file_next(t_list **files, t_file *file)
{
	close(file->fd_s);
	*files = (*files)->next;
}
