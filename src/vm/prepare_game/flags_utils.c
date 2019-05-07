/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:45:44 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/06 15:13:08 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

int		g_flags_match[8] = {
PARSE_NBR_CYCLES,
PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER | PARSE_FLAG_CHAMP_NBR
	| PARSE_CHAMP_NAME | PARSE_FLAG_VERBOSITY,
PARSE_CHAMP_NBR,
PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER | PARSE_FLAG_CHAMP_NBR
	| PARSE_CHAMP_NAME | PARSE_FLAG_VERBOSITY,
PARSE_CHAMP_NAME,
PARSE_FLAG_CHAMP_NBR | PARSE_CHAMP_NAME,
PARSE_VERBOSITY,
PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER | PARSE_FLAG_CHAMP_NBR
	| PARSE_CHAMP_NAME
};

void	turn_on_flags(int *bit_field, int on_flags)
{
	*bit_field |= on_flags;
}

int		choose_flags(int prev_input)
{
	int new_flags;

	new_flags = 0;
	turn_on_flags(&new_flags, g_flags_match[prev_input]);
	return (new_flags);
}
