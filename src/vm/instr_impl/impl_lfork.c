/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 19:09:20 by alex              #+#    #+#             */
/*   Updated: 2019/03/19 19:51:32 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	impl_lfork(t_vm_state *state, t_process *process, t_instr *instr)
{
	size_t	address;

	address = byte_order_swap(
		instr->instr_args[0].arg.direct.content, IND_SIZE).buffer;
	address = process->program_counter + address;
	vm_clone_process(state, address, process);
}
