/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:55:25 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/15 18:23:06 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"
#include "libft.h"

void	instr_init(t_instr *instr)
{
	ft_bzero(instr, sizeof(t_instr));
}
