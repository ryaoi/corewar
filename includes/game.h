/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:56:58 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/21 16:59:37 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GAME_H
# define _GAME_H

typedef struct	s_game_data
{
		int		cycles_to_die;
		int		live_since_dec;
		int		checks_since_dec;
}				t_game_data;


#endif
