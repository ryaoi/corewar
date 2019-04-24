/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champs_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 15:25:02 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/24 10:40:42 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int		get_champ_nbr(char *input, int index, t_corewar_input *cw_input)
{
	int	champ_nbr;

	champ_nbr = ft_atoi(input);
	if (cw_input->champ_flags >> (champ_nbr - 1) & 1)
		return (DUPLICATE_CHAMP_NBR);
	else
	{
		cw_input->champ_flags |= (1 << (champ_nbr - 1));
		cw_input->incoming_champion = champ_nbr;
	}
	return (index);
}

int		get_champ_name(char *input, int index, t_corewar_input *cw_input)
{
	int		i;

	i = 0;
	if (cw_input->incoming_champion == -1)
	{
		while (cw_input->champions[i])
			i++;
		if (!(cw_input->champions[i] = ft_strdup(input)))
			return (MALLOC_FAIL);
		cw_input->nbr_of_champions++;
	}
	else
	{
		if (!(cw_input->champions[cw_input->incoming_champion - 1] = ft_strdup(input)))
			return (MALLOC_FAIL);
		cw_input->nbr_of_champions++;
		cw_input->incoming_champion = -1;
	}
	return (index);
}
