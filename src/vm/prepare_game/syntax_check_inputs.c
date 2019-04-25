/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_inputs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:41:38 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/25 18:03:23 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

int		is_cycles(char *str, t_corewar_input *cw_input)
{
	int		index;

	(void)cw_input;
	index = 0;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (INVALID_SYNTAX);
		index++;
	}
	return (1);
}

int		is_champ_nbr(char *str, t_corewar_input *cw_input)
{
	int	index;
	int	champ_nbr;

	(void)cw_input;
	index = 0;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (INVALID_SYNTAX);
		index++;
	}
	champ_nbr = ft_atoi(str);
	if (champ_nbr < 1 || champ_nbr > 4)
		return (INVALID_CHAMP_NBR);
	return (1);
}

int		is_champ_name(char *str, t_corewar_input *cw_input)
{
	int		name_length;

	(void)cw_input;
	name_length = ft_strlen(str);
	if (name_length < 5)
		return (INVALID_CHAMP_NAMES_LENGTH);
	if (name_length > MAX_PROG_NAME_LENGTH_WITH_PATH)
		return (INVALID_CHAMP_NAMES_LENGTH);
	if ((str + name_length - EXTENSION_LENGTH)
			&& !ft_strcmp(".cor", str + name_length - EXTENSION_LENGTH))
		return (1);
	else
		return (-5);
}

int		is_verbosity(char *str, t_corewar_input *cw_input)
{
	int	index;
	int	log_level;

	(void)cw_input;
	index = 0;
	while (str[index])
	{
		if (!ft_isdigit(str[index]))
			return (INVALID_SYNTAX);
		index++;
	}
	log_level = ft_atoi(str);
	if (log_level < 1 || log_level > 1023)
		return (INVALID_SYNTAX);
	return (1);
}
