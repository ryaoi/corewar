/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cor_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:41:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 18:05:12 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void			write_bytecode(int fd, t_list *traverse)
{
	while (traverse)
	{
		if (((t_line*)traverse->content)->bytecode)
			write(fd, ((t_line*)traverse->content)->bytecode,
				((t_line*)traverse->content)->bytecode_len);
		traverse = traverse->next;
	}
}

unsigned char	*get_progsize(t_file *file) /*TODO need check..fuck */
{
	unsigned char	*ret;
	unsigned int	prog_size;
	t_list			*traverse;
	traverse = file->lines;
	prog_size = 0;
	while (traverse)
	{
		prog_size += LST_CONT(traverse, t_line).bytecode_len;
		traverse = traverse->next;
	}
	ft_printf("prog_size : %u\n", prog_size);
	ret = (unsigned char*)malloc(sizeof(unsigned char) * 4);
	ret[0] = prog_size >> 24;
	ret[1] = (prog_size << 8) >> 24;
	ret[2] = (prog_size << 16) >> 24;
	ret[3] = (prog_size << 24) >> 24;
	return (ret);
}

void			write_header_comment(int fd, t_file *file)
{
	unsigned char	magic[3];
	unsigned char	*prog_size;
	magic[0] = 0xea;
	magic[1] = 0x83;
	magic[2] = 0xf3;
	prog_size = get_progsize(file);
	write(fd, magic, 3);
	write(fd, file->header.prog_name, PROG_NAME_LENGTH);
	write(fd, prog_size, 4);
	write(fd, file->header.how, COMMENT_LENGTH);
}
int		write_cor_file(t_file *file)
{
	t_list *traverse;

	traverse = file->lines;
	if (!(file->fd_cor = open(file->name_cor, O_CREAT | O_WRONLY | O_TRUNC,
								0644)))
		ft_putendl("failed to create file.");
	write_header_comment(file->fd_cor, file);
	write_bytecode(file->fd_cor, traverse);
	return (SUCCESS);
}
