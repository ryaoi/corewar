/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:32:16 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/25 16:37:37 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

int		(*g_syntax_check[8])(char*, t_corewar_input*) = {
	is_flag_memdump,
	is_flag_visualizer,
	is_flag_champ_nbr,
	is_cycles,
	is_champ_nbr,
	is_champ_name,
	is_flag_verbosity,
	is_verbosity
};

char *g_log_level_tab[10] = {
"log_lives",
"log_cycles",
"log_instr",
"log_store",
"log_load",
"log_jump",
"log_fork",
"log_game",
"log_deaths",
"log_memdump"
};

void	print_usage(void)
{
	int		index;
	int		log_flag;

	index = 0;
	log_flag = 1;
	ft_printf("Usage : $> ./corewar [-dump N | -v] [-n N champion1.cor | champion1.cor] ...\n");
	ft_printf("\t\t-dump N : dumps memory after N cycles (N > 0)\n");
	ft_printf("\t\t-visu : turn on visualizer\n");
	ft_printf("\t\t-n N champion.cor : player N and name_of_champion.cor (0 < N < 5)\n");
	ft_printf("\t\t-v N : turn on log / N : log level (0 < N < 1024)\n");
	while (index < e_log_level_max)
	{
		ft_printf("\t\t\t%d : %s\n", log_flag, g_log_level_tab[index]);
		log_flag *= 2;
		index++;
	}
}

int		parse_input(char *input, int index, t_corewar_input *cw_input)
{

	if (index == 0)
		cw_input->exec_flags |= FLAG_MEMDUMP;
	else if (index == 1)
		cw_input->exec_flags |= FLAG_VISUALIZER;
	else if (index == 3)
		cw_input->nbr_of_cycles = ft_atoi(input);
	else if (index == 4)
		index = get_champ_nbr(input, index, cw_input);
	else if (index == 5)
		index = get_champ_name(input, index, cw_input);
	else if (index == 6)
		cw_input->exec_flags |= FLAG_VERBOSITY;
	else if (index == 7)
		index = get_log_verbosity(input, index, cw_input);
	return (index);
}

int		check_syntax(char *input, int flags, t_corewar_input *cw_input)
{
	int		index;
	int		ret_syncheck;
	int		ret;

	index = 0;
	while (index < (int)(sizeof(g_syntax_check) / sizeof(g_syntax_check[0])))
	{
		if ((flags >> index & 1)
				&& (ret_syncheck = g_syntax_check[index](input, cw_input)) > 0)
		{
			ret = parse_input(input, index, cw_input);
			return (ret);
		}
		index++;
	}
	print_usage();
	return (-1);
}

void	init_corewar_input(t_corewar_input *cw_input)
{
	int i;

	cw_input->nbr_of_champions = 0;
	cw_input->nbr_of_cycles = 0;
	cw_input->exec_flags = 0;
	cw_input->champ_flags = 0;
	cw_input->champions[0] = NULL;
	cw_input->champions[1] = NULL;
	cw_input->champions[2] = NULL;
	cw_input->champions[3] = NULL;
	cw_input->incoming_champion = -1;
	i = 0;
	while (i < e_log_level_max)
	{
		cw_input->log_verbosity[i] = 0;
		i++;
	}
}

int		parse_cmd(int argc, char **argv, t_corewar_input *cw_input)
{
	int				flags;
	int				index;
	int				ret;

	flags = PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER | PARSE_FLAG_VERBOSITY
							| PARSE_FLAG_CHAMP_NBR | PARSE_CHAMP_NAME;
	init_corewar_input(cw_input);
	index = 1;
	if (argc < 2)
	{
		print_usage();
		return (-1);
	}
	else
	{
		while (index < argc)
		{
			ret = check_syntax(argv[index], flags, cw_input);
			if (ret > -1)
				flags = choose_flags(ret);
			else
				return (-1);
			index++;
		}
	}
	if (cw_input->nbr_of_cycles == 0)
		cw_input->nbr_of_cycles = MAX_NBR_CYCLE;
	printf("nbr of champs : %d\n", cw_input->nbr_of_champions);
	printf("exec flags : %d\n", cw_input->exec_flags);
	printf("nbr of cycles : %zu\n", cw_input->nbr_of_cycles);
	printf("champ_flag : %d\n", cw_input->champ_flags);

	// for (int i=0; i < MAX_CHAMP_NBR; i++)
	// {
	// 	if (cw_input->champions[i] != NULL)
	// 		printf("champ[%d] : %s\n", i + 1, cw_input->champions[i]);
	// }
	return (FT_SUCCESS);
}
