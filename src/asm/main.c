/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:15:51 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 15:31:30 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	file_add(t_list **inputs, char *filename)
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
	int ret;

	while (traverse)
	{
		if ((ret = file_read((t_file*)traverse->content)) < 0)
		{
			print_errmsg_file_read(ret);
			file_next(&traverse, &LST_CONT(traverse, t_file));
			continue;
		}
		if (file_parse((t_file*)traverse->content) < 0 ||
			((t_file*)traverse->content)->prework_flag != PREWORK_FLAG_ON ||
			file_conversion(((t_file*)traverse->content)) < 0)
		{
			file_next(&traverse, &LST_CONT(traverse, t_file));
			continue;
		}
		write_cor_file(&LST_CONT(traverse, t_file));
		ft_printf("[%s] assembled.\n", LST_CONT(traverse, t_file).name_cor);
		file_next(&traverse, &LST_CONT(traverse, t_file));
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
	free_asm(inputs);
	return (0);
	/*TODO print .cor in hexadecimal with option*/
}
