/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:25:02 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/06 15:11:27 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

int		get_champ_nbr(char *input, int index, t_corewar_input *cw_input)
{
	int	champ_nbr;

	champ_nbr = ft_atoi(input);
	if (cw_input->champ_flags >> (champ_nbr - 1) & 1)
		return (DUPLICATE_CHAMP_NBR);
	else
	{
		cw_input->champ_flags |= (1 << (champ_nbr - 1));
		cw_input->champ_id = champ_nbr;
	}
	return (index);
}

int		get_champ_name(char *input, int index, t_corewar_input *cw_input)
{
	int		i;

	i = 0;
	if (cw_input->nbr_of_champions > 3)
	{
		ft_printf("Too many champions!!\n");
		return (TOO_MANY_PLAYERS);
	}
	if (cw_input->champ_id == -1)
	{
		while (cw_input->champions[i])
			i++;
		if (!(cw_input->champions[i] = ft_strdup(input)))
			return (MALLOC_FAIL);
		cw_input->nbr_of_champions++;
		cw_input->champ_flags |= (1 << i);
	}
	else
	{
		if (!(cw_input->champions[cw_input->champ_id - 1] = ft_strdup(input)))
			return (MALLOC_FAIL);
		cw_input->nbr_of_champions++;
		cw_input->champ_id = -1;
	}
	return (index);
}

int		get_log_verbosity(char *input, int index, t_corewar_input *cw_input)
{
	int	i;
	int	verbosity;

	i = 0;
	verbosity = ft_atoi(input);
	while (i < e_log_level_max)
	{
		if (verbosity & (1 << i))
			cw_input->log_verbosity[i] = 1;
		i++;
	}
	return (index);
}
