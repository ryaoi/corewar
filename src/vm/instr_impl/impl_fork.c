/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:09:20 by alex              #+#    #+#             */
/*   Updated: 2019/03/20 17:13:12 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_fork(t_vm_state *state, t_process *process, t_instr *instr)
{
	int64_t	offset;

	offset = byte_order_swap(
		instr->instr_args[0].arg.direct.content).buffer;
	offset = process->program_counter + (offset % IDX_MOD);
	vm_clone_process(state, offset, process);
}
