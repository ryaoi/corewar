/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:41:47 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/24 19:59:40 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"

int		is_flag_memdump(char *str, t_corewar_input *cw_input)
{
	if (cw_input->exec_flags & FLAG_MEMDUMP)
		return (DUPLICATE_SYMBOLS);
	if (!ft_strcmp("-dump", str))
		return (1);
	else
		return (INVALID_SYNTAX);
}

int		is_flag_visualizer(char *str, t_corewar_input *cw_input)
{
	if (cw_input->exec_flags & FLAG_VISUALIZER)
		return (DUPLICATE_SYMBOLS);
	if (!ft_strcmp("-visu", str))
		return (1);
	else
		return (INVALID_SYNTAX);
}

int		is_flag_champ_nbr(char *str, t_corewar_input *cw_input)
{
	(void)cw_input;
	if (!ft_strcmp("-n", str))
		return (1);
	else
		return (INVALID_SYNTAX);
}

int		is_flag_verbosity(char *str, t_corewar_input *cw_input)
{
	(void)cw_input;
	if (cw_input->exec_flags & FLAG_VERBOSITY)
		return (DUPLICATE_SYMBOLS);
	if (!ft_strcmp("-v", str))
		return (1);
	else
		return (INVALID_SYNTAX);
}
