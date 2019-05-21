/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:56:58 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/21 19:10:57 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GAME_H
# define _GAME_H

# include "vm.h"
# include "array.h"

typedef struct	s_game_data
{
	t_vm_state	state;
	int			last_check;
	int			cycles_to_die;
	int			live_since_dec;
	int			checks_since_dec;
}				t_game_data;

void			prepare_game(t_game_data *game, t_array *players,
					const t_log_info *log_opts);
int				advance_cycle(t_game_data *game);

#endif
