/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 16:32:14 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/17 17:38:55 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

void	dump_memory(t_vm_state *state)
{
	size_t	line;
	size_t	index;
	size_t	line_size;

	line_size = ft_sqrt(MEM_SIZE);
	line = 0;
	while (line < (MEM_SIZE / line_size))
	{
		index = 0;
		ft_printf("%6.4p : ", (void*)(line * (MEM_SIZE / line_size)));
		while (index < line_size)
		{
			ft_printf("%.2hhx ",
				state->memory[(line * (MEM_SIZE / line_size)) + index]);
			index++;
		}
		ft_printf("\n");
		line++;
	}
}
