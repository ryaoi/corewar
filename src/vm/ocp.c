/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:15:38 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/18 19:19:31 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_ocp	parse_ocp(uint8_t byte)
{
	size_t	index;
	uint8_t	field;
	t_ocp	ocp;

	ft_bzero(&ocp, sizeof(t_ocp));
	index = 0;
	while (index < 3)
	{
		field = (byte >> ((index + 1) * 2)) & 0b11;
		if (field == 0b00)
			ocp.fields[(3 - 1) - index] = e_absent;
		else if (field == 0b01)
			ocp.fields[(3 - 1) - index] = e_register;
		else if (field == 0b10)
			ocp.fields[(3 - 1) - index] = e_direct;
		else
			ocp.fields[(3 - 1) - index] = e_index;
		index++;
	}
	return (ocp);
}
