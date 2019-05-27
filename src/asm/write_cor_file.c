/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cor_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:41:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/27 18:09:31 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

static void				write_bytecode(int fd, t_list *traverse)
{
	unsigned char buf4[4];

	ft_bzero(buf4, 4);
	write(fd, buf4, 4);
	while (traverse)
	{
		if (((t_line*)traverse->content)->type == e_asmcode)
			write(fd, ((t_line*)traverse->content)->bytecode,
				((t_line*)traverse->content)->bytecode_len);
		traverse = traverse->next;
	}
}

static unsigned char	*get_progsize(t_file *file)
{
	unsigned char	*ret;
	unsigned int	prog_size;
	t_list			*traverse;

	traverse = file->lines;
	prog_size = 0;
	while (traverse)
	{
		prog_size += ((t_line*)traverse->content)->bytecode_len;
		traverse = traverse->next;
	}
	if (!(ret = (unsigned char*)malloc(sizeof(unsigned char) * 4)))
		return (NULL);
	ret[0] = prog_size >> 24;
	ret[1] = (prog_size << 8) >> 24;
	ret[2] = (prog_size << 16) >> 24;
	ret[3] = (prog_size << 24) >> 24;
	return (ret);
}

static void				write_header_comment(int fd, t_file *file)
{
	unsigned char	magic[3];
	unsigned char	*prog_size;
	unsigned char	buf1[1];
	unsigned char	buf4[4];

	magic[0] = 0xea;
	magic[1] = 0x83;
	magic[2] = 0xf3;
	ft_bzero(buf1, 1);
	ft_bzero(buf4, 4);
	prog_size = get_progsize(file);
	write(fd, buf1, 1);
	write(fd, magic, 3);
	write(fd, file->header.prog_name, PROG_NAME_LENGTH);
	write(fd, buf4, 4);
	write(fd, prog_size, 4);
	write(fd, file->header.comment, COMMENT_LENGTH);
	free(prog_size);
}

int						write_cor_file(t_file *file)
{
	t_list *traverse;

	traverse = file->lines;
	if ((file->fd_cor = open(file->name_cor, O_CREAT | O_WRONLY | O_TRUNC,
								0644)) == -1)
	{
		ft_putendl("failed to create file.");
		return (e_create_file_fail);
	}
	write_header_comment(file->fd_cor, file);
	write_bytecode(file->fd_cor, traverse);
	return (FT_SUCCESS);
}
