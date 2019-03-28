/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:15:51 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/28 18:47:36 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

static int	file_name_check(const char *filename, t_file *file)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(filename);
	if (len < 3 || filename[len - 2] != '.' || filename[len - 1] != 's')
		ERROR("the filename has to exist and ends with '.s'", 0);
	if ((file->fd_s = open(filename, O_RDONLY)) == -1)
		ERROR("failed to open the file.", 0);
	if (!(file->name_s = ft_strdup(filename)))
		ERROR("ft_strdup failed", 0);
	if (!(tmp = (char*)ft_strsub(filename, 0, len - 2)))
		ERROR("ft_strndup failed", 0);
	if (!(file->name_cor = ft_strjoin(tmp, ".cor")))
		ERROR("ft_strjoin failed", 0);
	free(tmp);
	return (SUCCESS);
}

static int	argv_check(int argc, char **argv, int *option)
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
	//else if(argc != 2)
	//	file_error("Too many files. Usage: ./asm [filename.s] [-p]", file);
			/* TODO remove after implementing multiple file handler */
}

static void	file_init(t_file *file)
{
	file->lines = NULL;
	file->nbr_line = 0;
	file->name_s = NULL;
	file->name_cor = NULL;
	file->fd_s = -1;
	file->fd_cor = -1;
	file->header_flags = OFF;
	ft_bzero(&(file->header.prog_name[0]), PROG_NAME_LENGTH + 1);
	ft_bzero(&(file->header.how[0]), COMMENT_LENGTH + 1);
}

static void	file_add(t_list **inputs, char *filename)
{
	t_file	file;

	file_init(&file);
	if (file_name_check(filename, &file) == FILE_ERROR)
		ft_putendl("file name is invalid. skip!");
	else
		list_append(inputs, list_new(&file, sizeof(file)));
}

int		main(int argc, char **argv)
{
	t_list	*inputs;
	t_list	*traverse;
	int		index;
	int		option;

	option = 0;
	inputs = NULL;
	if (argv_check(argc, argv, &option) == FILE_ERROR)
	{
		ft_putendl("argv_check() failed.");
		return (0);
	}
	index = option == ON ? 2 : 1;
	while (index < argc)
		file_add(&inputs, argv[index++]);
	traverse = inputs;
	printf("%p\n", traverse);
	while (traverse)
	{
		if (file_read((t_file*)traverse->content) == FILE_ERROR)
		{
			ft_printf("file_read() on %s failed.\n", ((t_file*)traverse->content)->name_s);
			close(((t_file*)traverse->content)->fd_s);
			traverse = traverse->next;
			continue ;
		}
		if (file_parse((t_file*)traverse->content) == LINE_FAIL)
		{
			ft_printf("file_parse() on %s failed.\n", ((t_file*)traverse->content)->name_s);
			close(((t_file*)traverse->content)->fd_s);
			traverse = traverse->next;
			continue ;
		}
		if (((t_file*)traverse->content)->header_flags == OFF)
		{
			ft_printf("header not found in %s.\n", ((t_file*)traverse->content)->name_s);
			close(((t_file*)traverse->content)->fd_s);
			traverse = traverse->next;
			continue ;
		}
		if (file_conversion(((t_file*)traverse->content)) == CONVERSION_FAIL)
		{
			ft_printf("file_conversion() on %s failed.\n", ((t_file*)traverse->content)->name_s);
			close(((t_file*)traverse->content)->fd_s);
			traverse = traverse->next;
			continue ;
		}
		close(((t_file*)traverse->content)->fd_s);
		write_cor_file(((t_file*)traverse->content));
		ft_printf("%s successfully created.\n", ((t_file*)traverse->content)->name_cor);
		traverse = traverse->next;
	}
	ft_exit(inputs);
	return (0);
	/*TODO handle multiple .s files, print .cor in hexadecimal with option*/
}
