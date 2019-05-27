/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_short.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:23:23 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 17:24:31 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_register	*register_get(t_process *process, size_t id)
{
	return (&(process->registers[id]));
}
