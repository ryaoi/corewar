/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 19:14:07 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/15 20:03:07 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"

void	impl_live(t_vm_state *state, t_process *process, t_instr *instr)
{
	size_t	parameter;

	parameter = *(size_t*)byte_order_swap(
		instr->instr_args[0].arg.direct.content, DIR_SIZE).buffer;
	ARRAY_PTR(state->processes, t_process)[parameter].live++;
}
