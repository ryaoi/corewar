/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:09:20 by alex              #+#    #+#             */
/*   Updated: 2019/03/19 17:15:30 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"

void	impl_fork(t_vm_state *state, t_process *process, t_instr *instr)
{
	size_t	address;

	address = byte_order_swap(
		instr->instr_args[0].arg.direct.content, IND_SIZE).buffer;
	address = process->program_counter + (address % IDX_MOD);
	vm_spawn_process(state, address, process);
}
