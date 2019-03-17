/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:09:20 by alex              #+#    #+#             */
/*   Updated: 2019/03/17 19:19:16 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"

void	impl_fork(t_vm_state *state, t_process *process, t_instr *instr)
{
	size_t	address;

	address = *(size_t*)byte_order_swap(
		instr->instr_args[0].arg.direct.content, IND_SIZE).buffer;
	address = process->program_counter + (address % IDX_MOD);
	vm_spawn_process(state, address, process);
}