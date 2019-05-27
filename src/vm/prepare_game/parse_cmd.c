/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:32:16 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/27 19:23:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

int		(*const g_syntax_check[8])(char*, t_corewar_input*) = {
	is_flag_memdump,
	is_flag_visualizer,
	is_flag_champ_nbr,
	is_cycles,
	is_champ_nbr,
	is_champ_name,
	is_flag_verbosity,
	is_verbosity
};

void		check_flags_conflicts(t_corewar_input *cw_input)
{
	if (cw_input->exec_flags & FLAG_VISUALIZER)
	{
		ft_bzero(cw_input->log_verbosity, e_log_level_max);
		cw_input->exec_flags &= ~FLAG_MEMDUMP;
		cw_input->nbr_of_cycles = SIZE_T_MAX;
	}
}

int		parse_input(char *input, int index, t_corewar_input *cw_input)
{
	if (index == 0)
		cw_input->exec_flags |= FLAG_MEMDUMP;
	else if (index == 1)
		cw_input->exec_flags |= FLAG_VISUALIZER;
	else if (index == 3)
		cw_input->nbr_of_cycles = ft_a_to_sizet(input);
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
	cw_input->nbr_of_cycles = SIZE_T_MAX;
	cw_input->exec_flags = 0;
	cw_input->champ_flags = 0;
	cw_input->champions[0] = NULL;
	cw_input->champions[1] = NULL;
	cw_input->champions[2] = NULL;
	cw_input->champions[3] = NULL;
	cw_input->champ_id = -1;
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
	while (index < argc)
	{
		ret = check_syntax(argv[index], flags, cw_input);
		if (ret > -1)
			flags = choose_flags(ret);
		else
			return (-1);
		index++;
	}
	check_flags_conflicts(cw_input);
	return (FT_SUCCESS);
}
