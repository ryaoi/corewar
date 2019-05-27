/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_short.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:12:22 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 17:15:29 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_process	*process_get(t_vm_state *state, size_t id)
{
	return (&((t_process*)state->processes.ptr)[id]);
}

t_player	*player_get(t_vm_state *state, size_t id)
{
	return (&((t_player*)state->players.ptr)[id]);
}
