/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:15:51 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/16 16:43:51 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

static void	check_file_name(const char *filename, t_file *file)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(filename);
	if (len < 3 || filename[len - 2] != '.' || filename[len - 1] != 's')
		file_error("the filename has to end with '.s'", file);
	if ((file->fd_s = open(filename, O_RDONLY)) == -1)
		file_error("failed to open the file.", file);
	if (!(file->name_s = ft_strdup(filename)))
		file_error("ft_strdup failed", file);
	if (!(tmp = (char*)ft_strsub(filename, 0, len - 2)))
		file_error("ft_strndup failed", file);
	if (!(file->name_cor = ft_strjoin(tmp, ".cor")))
		file_error("ft_strjoin failed", file);
	free(tmp);
}

static void	check_file(int argc, t_file *file)
{
		if (argc == 1)
			file_error("no file identified", file);
		if (argc > 2)
			file_error("too many files", file);
}

static void	init_file(t_file *file)
{
	file->lines = NULL;
	file->nbr_line = 0;
	file->name_s = NULL;
	file->name_cor = NULL;
	file->fd_s = -1;
	file->fd_cor = -1;
	ft_bzero(&(file->header.prog_name[0]), PROG_NAME_LENGTH + 1);
	ft_bzero(&(file->header.how[0]), COMMENT_LENGTH + 1);
}

int		main(int argc, char **argv)
{
	t_file	file;

	init_file(&file);
	check_file(argc, &file);
	check_file_name(argv[1], &file);
	read_file(&file);
	if (parse_file(&file) == LINE_FAIL)
		file_error("parse_file() failed.", &file);
	return (0);
}
