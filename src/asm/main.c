/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:15:51 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/27 14:54:00 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	file_add(t_list **inputs, char *filename)
{
	t_file	file;
	int		ret;

	file_init(&file);
	if ((ret = file_name_check(filename, &file)) < 0)
		print_errmsg_file(ret, filename);
	else
		list_append(inputs, list_new(&file, sizeof(file)));
}

void	assemble_file(t_list *traverse)
{
	int ret;

	while (traverse)
	{
		ft_printf("'%s' compiling ...\n", ((t_file*)traverse->content)->name_s);
		if ((ret = file_read((t_file*)traverse->content)) >= 0)
		{
			if (file_parse(((t_file*)traverse->content)) >= 0 &&
				file_conversion(((t_file*)traverse->content)) >= 0)
				if (write_cor_file(((t_file*)traverse->content)) >= 0)
					ft_printf("'%s' assembled!\n\n",
								((t_file*)traverse->content)->name_cor);
		}
		else
			print_errmsg_file_read(ret);
		close(((t_file*)traverse->content)->fd_s);
		traverse = traverse->next;
	}
}

int		main(int argc, char **argv)
{
	t_list	*inputs;
	int		index;

	inputs = NULL;
	if (argv_check(argc) == e_cmd_line_error)
		return (0);
	index = 1;
	while (index < argc)
		file_add(&inputs, argv[index++]);
	assemble_file(inputs);
	free_asm(inputs);
	return (0);
}
