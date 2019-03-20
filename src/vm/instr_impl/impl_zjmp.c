/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:40:48 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/20 15:22:29 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_zjmp(t_vm_state *state, t_process *process, const t_instr *instr)
{
	int64_t	offset;

	(void)state;
	offset = byte_order_swap(instr->instr_args[0].arg.direct.content).buffer;
	process->program_counter = process->program_counter + (offset % IDX_MOD);
}
