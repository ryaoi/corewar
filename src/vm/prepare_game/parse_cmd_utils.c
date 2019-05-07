/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:06:15 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/07 16:19:09 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

const char	*g_log_level_tab[10] = {
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

static size_t	skip_whitespaces(const char *str)
{
	size_t index;

	index = 0;
	while (str[index] && ft_isspace(str[index]))
		index++;
	return (index);
}

size_t			ft_a_to_sizet(const char *str)
{
	size_t	index;
	size_t	result;
	int		sign;

	result = 0;
	sign = 1;
	index = skip_whitespaces(str);
	if (str[index] == '+' || str[index] == '-')
		index++;
	while (str[index] && ft_isdigit(str[index]))
	{
		result *= 10;
		result = result + (str[index] - '0') * sign;
		index++;
	}
	return (result);
}

void			print_usage(void)
{
	int		index;
	int		log_flag;

	index = 0;
	log_flag = 1;
	ft_printf("Usage : $> ./corewar [-dump N | -v] ");
	ft_printf("[-n N champion1.cor | champion1.cor] ...\n");
	ft_printf("\t\t-dump N : dumps memory after N cycles ");
	ft_printf("(0 < N < SIZE_T_MAX)\n");
	ft_printf("\t\t-visu : turn on visualizer\n");
	ft_printf("\t\t-n N champion.cor : player N ");
	ft_printf("and name_of_champion.cor (0 < N < 5)\n");
	ft_printf("\t\t-v N : turn on log / N : log level (0 < N < 1024)\n");
	while (index < e_log_level_max)
	{
		ft_printf("\t\t\t%d : %s\n", log_flag, g_log_level_tab[index]);
		log_flag *= 2;
		index++;
	}
}
