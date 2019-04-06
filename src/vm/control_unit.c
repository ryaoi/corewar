/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_unit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:16:51 by aamadori          #+#    #+#             */
/*   Updated: 2019/04/06 19:03:04 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static size_t	parse_argument(t_vm_state *state, t_instr *instr,
					size_t argument, size_t address)
{
	t_bigend_buffer	load_arg;

	load_arg.buffer = 0;
	if (ARG_TYPE(instr, argument) == e_register)
	{
		load_arg = mem_load(state, address + instr->size, 1);
		ARG_REG(instr, argument)
			= ((uint8_t*)&load_arg.buffer)[sizeof(load_arg.buffer) - 1];
		if (!ARG_REG(instr, argument)
			|| ARG_REG(instr, argument) > REG_NUMBER)
			instr->invalid = 1;
		return (1);
	}
	else if (ARG_TYPE(instr, argument) == e_index)
	{
		load_arg = mem_load(state, address + instr->size, IND_SIZE);
		ARG_IND(instr, argument).content = load_arg;
		return (2);
	}
	else if (ARG_TYPE(instr, argument) == e_direct)
	{
		if (g_opcode_table[instr->opcode].relative)
		{
			load_arg = mem_load(state, address + instr->size, IND_SIZE);
			ARG_DIR(instr, argument).content = load_arg;
			return (2);
		}
		else
		{
			load_arg = mem_load(state, address + instr->size, DIR_SIZE);
			ARG_DIR(instr, argument).content = load_arg;
			return (4);
		}
	}
	else
		return (0);
}

static void		parse_instruction(t_vm_state *state, t_instr *instr,
					size_t address)
{
	int				arg_index;
	t_ocp			ocp;
	t_bigend_buffer	load_buffer;

	if (g_opcode_table[instr->opcode].has_ocp)
	{
		load_buffer = mem_load(state, address + instr->size, 1);
		ocp = parse_ocp(((uint8_t*)&load_buffer.buffer)[sizeof(load_buffer.buffer) - 1]);
		arg_types_ocp(instr, ocp);
		instr->size++;
	}
	else
		arg_types_non_ocp(instr);
	arg_index = 0;
	while (arg_index < g_opcode_table[instr->opcode].arg_num)
	{
		instr->size += parse_argument(state, instr, arg_index, address);
		arg_index++;
	}
}

t_instr			fetch_arguments(t_vm_state *state, enum e_instr opcode, size_t address)
{
	t_instr			instr;

	instr_init(&instr);
	if (opcode < e_invalid)
	{
		instr.opcode = opcode;
		instr.cost = g_opcode_table[instr.opcode].cycles;
		instr.size = 1;
		parse_instruction(state, &instr, address);
	}
	else
	{
		instr.opcode = e_invalid;
		instr.cost = 1;
		instr.size = 1;
		instr.invalid = 1;
	}
	return (instr);
}

enum e_instr	fetch_opcode(t_vm_state *state, size_t address)
{

	t_bigend_buffer	load_buffer;
	enum e_instr	opcode;

	load_buffer = mem_load(state, address, 1);
	opcode = ((uint8_t*)&load_buffer.buffer)[sizeof(load_buffer.buffer) - 1] - 1;
	if (opcode > e_invalid)
		opcode = e_invalid;
	return (opcode);
}
