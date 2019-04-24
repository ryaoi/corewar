/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:32:16 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/24 10:39:57 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int		(*g_syntax_check[6])(char*, t_corewar_input*) = {
	is_flag_memdump,
	is_flag_visualizer,
	is_flag_champ_nbr,
	is_cycles,
	is_champ_nbr,
	is_champ_name
};

#include <stdio.h>

void	print_usage(int	err_type)
{
	if (err_type == 0)
	{
		printf("Usage : $> ./corewar [-dump N | -v] [-n N champion1.cor] ...\n");
		printf("\t\t-dump N : dumps memory after N cycles\n");
		printf("\t\t-v : turn on visualizer\n");
		printf("\t\t-n N champion.cor : player N and name_of_champion.cor\n");
	}
}

int		parse_input(char *input, int index, t_corewar_input *cw_input)
{

	if (index == 0)
		cw_input->exec_flags |= FLAG_MEMDUMP;
	else if (index == 1)
		cw_input->exec_flags |= FLAG_VISUALIZER;
	else if (index == 2)
		cw_input->exec_flags |= FLAG_CHAMP_NBR;
	else if (index == 3)
		cw_input->nbr_of_cycles = ft_atoi(input);
	else if (index == 4)
		index = get_champ_nbr(input, index, cw_input);
	else if (index == 5)
		index = get_champ_name(input, index, cw_input);
	return (index);
}

int		check_syntax(int argc, char *input, int flags, t_corewar_input *cw_input)
{
	int	index;
	int	ret_syncheck;
	int	ret;

	index = 0;
	printf("argv %s\n", input);
	while (index < sizeof(g_syntax_check) / sizeof(g_syntax_check[0]))
	{
		if ((flags >> index & 1)
				&& (ret_syncheck = g_syntax_check[index](input, cw_input)) > 0)
		{
			ret = parse_input(input, index, cw_input);
			return (ret);
		}
		index++;
	}
	print_usage(0);
	return (-1);
}

void	init_corewar_input(t_corewar_input *cw_input)
{
	cw_input->nbr_of_champions = 0;
	cw_input->nbr_of_cycles = 0;
	cw_input->exec_flags = 0;
	cw_input->champ_flags = 0;
	cw_input->champions[0] = NULL;
	cw_input->champions[1] = NULL;
	cw_input->champions[2] = NULL;
	cw_input->champions[3] = NULL;
	cw_input->incoming_champion = -1;
}

int		main(int argc, char **argv)
{
	int				flags;
	int				index;
	int				ret;
	t_corewar_input	corewar_input;

	flags = PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER
							| PARSE_FLAG_CHAMP_NBR | PARSE_CHAMP_NAME;
	init_corewar_input(&corewar_input);
	index = 1;
	if (argc < 2)
		print_usage(0);
	else
	{
		while (index < argc)
		{
			ret = check_syntax(argc, argv[index], flags, &corewar_input);
			if (ret > -1)
				flags = choose_flags(ret);
			else
				return (-1);
			index++;
		}
	}
	for (int j=0; j < 4; j++)
	{
		if (corewar_input.champions[j] != NULL)
			printf("champ[%d] = %s\n", j+1, corewar_input.champions[j]);
	}
	return (0);
}
