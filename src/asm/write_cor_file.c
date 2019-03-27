/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_cor_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:41:20 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/27 21:39:24 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

void write_bytecode(int fd, t_list *traverse)
{
	while (traverse)
	{
		if (((t_line*)traverse->content)->bytecode)
			write(fd, ((t_line*)traverse->content)->bytecode,
				((t_line*)traverse->content)->bytecode_len);
		traverse = traverse->next;
	}
}

void write_header_comment(int fd, t_file *file)
{
	write(fd, file->header.prog_name, PROG_NAME_LENGTH);
	write(fd, file->header.how, COMMENT_LENGTH);
	/*TODO magic, prog_size ???? wtf*/
}

int write_cor_file(t_file *file)
{
	t_list *traverse;

	traverse = file->lines;
	if (!(file->fd_cor = open(file->name_cor, O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		ERROR("cannot create .cor fuck!!.", 0);
	write_header_comment(file->fd_cor, file);
	write_bytecode(file->fd_cor, traverse);
	return (SUCCESS);
}
