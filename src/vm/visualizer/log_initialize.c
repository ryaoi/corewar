/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_initialize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:08:59 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/25 16:17:12 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_line.h"
#include "logging.h"
#include "vm.h"
#include "game.h"


void	initialize_logging(t_log_info *info, t_corewar_input *cw_input)
{
	logs_init(info);
	ft_memcpy(info->log_active,
		cw_input->log_verbosity, sizeof(info->log_active));
}
