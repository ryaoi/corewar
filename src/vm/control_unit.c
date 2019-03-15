/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_unit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:16:51 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/15 16:46:22 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "cpu.h"

t_instr		fetch_instruction(t_vm_state *state, size_t	address)
{
	size_t			match_index;
	t_load_buffer	opcode;
	t_instr			err;

	match_index = 0;
	opcode = mem_load(state, address, 1);
	while (match_index < sizeof(g_opcode_table)/sizeof(g_opcode_table[0]))
	{
		if (opcode.buffer[0] == g_opcode_table[match_index].opcode)
		{
			return ((g_parser_table[match_index])(state, address));
		}
		match_index++;
	}
	err.opcode = e_invalid;
	return (err);
}
