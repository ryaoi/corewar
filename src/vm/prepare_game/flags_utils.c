/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 14:45:44 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/24 19:50:39 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"
/*
typedef struct	s_input_flags
{
	int	on;
	int off;
}				t_input_flags;

t_input_flags	g_flags_match[6] = {

	{PARSE_NBR_CYCLES,
	PARSE_FLAG_MEMDUMP | PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER
		| PARSE_CHAMP_NBR | PARSE_CHAMP_NAME},

	{PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER | PARSE_FLAG_CHAMP_NBR
		| PARSE_CHAMP_NAME,
	PARSE_FLAG_VISUALIZER},

	{PARSE_CHAMP_NBR,
	PARSE_FLAG_MEMDUMP | PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER
		| PARSE_CHAMP_NBR | PARSE_CHAMP_NAME},

	{PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER | PARSE_FLAG_CHAMP_NBR
		| PARSE_CHAMP_NAME,
	PARSE_NBR_CYCLES},

	{PARSE_CHAMP_NAME,
	PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER | PARSE_FLAG_CHAMP_NBR
		| PARSE_NBR_CYCLES | PARSE_CHAMP_NBR},

	{PARSE_CHAMP_NBR | PARSE_CHAMP_NAME,
	PARSE_FLAG_MEMDUMP | PARSE_FLAG_VISUALIZER | PARSE_FLAG_CHAMP_NBR
		| PARSE_NBR_CYCLES}
};
*/

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
