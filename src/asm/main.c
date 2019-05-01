/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:15:51 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/01 20:58:35 by jaelee           ###   ########.fr       */
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
		ft_printf("compiling '%s'...\n", LST_CONT(traverse, t_file).name_cor);
		if ((ret = file_read((t_file*)traverse->content)) < 0)
		{
			print_errmsg_file_read(ret);
			file_next(&traverse, &LST_CONT(traverse, t_file));
			continue;
		}
		if (file_parse(&LST_CONT(traverse, t_file)) < 0 ||
			file_conversion(&LST_CONT(traverse, t_file)) < 0)
		{
			file_next(&traverse, &LST_CONT(traverse, t_file));
			continue;
		}
		if (write_cor_file(&LST_CONT(traverse, t_file)) < 0)
		{
			file_next(&traverse, &LST_CONT(traverse, t_file));
			continue;
		}
		ft_printf("'%s' assembled!\n\n", LST_CONT(traverse, t_file).name_cor);
		file_next(&traverse, &LST_CONT(traverse, t_file));
	}
}

int		main(int argc, char **argv)
{
	t_list	*inputs;
	int		index;

	inputs = NULL;
	if (argv_check(argc) == FILE_ERROR)
		return (0);
	index = 1;
	while (index < argc)
		file_add(&inputs, argv[index++]);
	assemble_file(inputs);
	free_asm(inputs);
	return (0);
}
