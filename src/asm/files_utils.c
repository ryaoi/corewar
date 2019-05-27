/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:12:52 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/27 15:26:18 by jaelee           ###   ########.fr       */
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
	ft_bzero(&(file->header.comment[0]), COMMENT_LENGTH + 1);
}

int		file_name_check(const char *filename, t_file *file)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(filename);
	if (len < 3 || filename[len - 2] != '.' || filename[len - 1] != 's')
		return (e_dot_s_error);
	if ((file->fd_s = open(filename, O_RDONLY)) == -1)
		return (e_open_file_error);
	if (!(file->name_s = ft_strdup(filename)))
		return (e_strdup_fail);
	if (!(tmp = (char*)ft_strsub(filename, 0, len - 2)))
		return (e_strndup_fail);
	if (!(file->name_cor = ft_strjoin(tmp, ".cor")))
	{
		free(tmp);
		return (e_strjoin_fail);
	}
	free(tmp);
	return (FT_SUCCESS);
}

int		argv_check(int argc)
{
	if (argc == 1)
	{
		ft_putendl("no file identified.");
		ft_putendl("Usage: ./asm [filename_A.s] [filename_B.s] ...");
		return (e_cmd_line_error);
	}
	return (FT_SUCCESS);
}

void	file_next(t_list **files, t_file *file)
{
	close(file->fd_s);
	*files = (*files)->next;
}
