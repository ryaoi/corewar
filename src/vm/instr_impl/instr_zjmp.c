/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_zjmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 19:40:48 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/16 19:51:42 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"

void	impl_zjmp(t_vm_state *state, t_process *process, t_instr *instr)
{
	size_t	address;

	address = *(size_t*)byte_order_swap(
		instr->instr_args[0].arg.direct.content, IND_SIZE).buffer;
	process->program_counter = process->program_counter + (address % IDX_MOD);
}