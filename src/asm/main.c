/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:15:51 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/06 19:08:06 by jaelee           ###   ########.fr       */
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
}

static void	file_init(t_file *file)
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

void	print_errmsg_file(int err_type)
{
	if (err_type == DOT_S_ERROR)
		ft_putendl("the filename has to exist and ends with '.s'");
	else if (err_type == OPEN_FILE_ERROR)
		ft_putendl("failed to open the file.");
	else if (err_type == STRDUP_FAIL)
		ft_putendl("ft_strdup failed.");
	else if (err_type == STRNDUP_FAIL)
		ft_putendl("ft_strndup failed.");
	else if (err_type == STRJOIN_FAIL)
		ft_putendl("ft_strjoin failed.");
}

static void	file_add(t_list **inputs, char *filename)
{
	t_file	file;
	int		ret;

	file_init(&file);
	if ((ret = file_name_check(filename, &file)) < 0)
		print_errmsg_file(ret);
	else
		list_append(inputs, list_new(&file, sizeof(file)));
}

void	assemble_file(t_list *traverse)
{
	while (traverse)
	{
		if (file_read((t_file*)traverse->content) == FILE_ERROR ||
			file_parse((t_file*)traverse->content) == LINE_FAIL ||
			((t_file*)traverse->content)->prework_flag != PREWORK_FLAG_ON ||
			file_conversion(((t_file*)traverse->content)) == CONVERSION_FAIL
			)
		{
			ft_printf("%s cannot be parsed.\n",
						LST_CONT(traverse, t_file).name_s);
			close(LST_CONT(traverse, t_file).fd_s);
			traverse = traverse->next;
			continue;
		}
		close(LST_CONT(traverse, t_file).fd_s);
		write_cor_file(&LST_CONT(traverse, t_file));
		ft_printf("%s successfully created.\n",
					LST_CONT(traverse, t_file).name_cor);
		traverse = traverse->next;
	}
}

int		main(int argc, char **argv)
{
	t_list	*inputs;
	int		index;
	int		option;

	option = 0;
	inputs = NULL;
	if (argv_check(argc, argv, &option) == FILE_ERROR)
		return (0);
	index = option == ON ? 2 : 1;
	while (index < argc)
		file_add(&inputs, argv[index++]);
	assemble_file(inputs);
	ft_exit(inputs);
	return (0);
	/*TODO handle multiple .s files, print .cor in hexadecimal with option*/
}
