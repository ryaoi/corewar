/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_unit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:16:51 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/23 17:15:23 by jaelee           ###   ########.fr       */
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
		ARG_REG(instr, argument) = INDEX_BUFF(load_arg, L_BUFF_SIZE - 1);
		if (!ARG_REG(instr, argument) || ARG_REG(instr, argument) > REG_NUMBER)
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
		load_arg = mem_load(state, address + instr->size,
			g_op_tab[instr->opcode].relative ? IND_SIZE : DIR_SIZE);
		ARG_DIR(instr, argument).content = load_arg;
		return (g_op_tab[instr->opcode].relative ? 2 : 4);
	}
	return (0);
}

static void		parse_instruction(t_vm_state *state, t_instr *instr,
					size_t address)
{
	int				arg_index;
	t_ocp			ocp;
	t_bigend_buffer	load_buffer;

	if (g_op_tab[instr->opcode].has_ocp)
	{
		load_buffer = mem_load(state, address + instr->size, 1);
		ocp = parse_ocp(INDEX_BUFF(load_buffer, L_BUFF_SIZE - 1));
		arg_types_ocp(instr, ocp);
		instr->size++;
	}
	else
		arg_types_non_ocp(instr);
	arg_index = 0;
	while (arg_index < g_op_tab[instr->opcode].arg_num)
	{
		instr->size += parse_argument(state, instr, arg_index, address);
		arg_index++;
	}
}

t_instr			fetch_arguments(t_vm_state *state, enum e_instr opcode,
					size_t address)
{
	t_instr			instr;

	instr_init(&instr);
	if (opcode < e_invalid)
	{
		instr.opcode = opcode;
		instr.cost = g_op_tab[instr.opcode].cycles;
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
	opcode = INDEX_BUFF(load_buffer, L_BUFF_SIZE - 1) - 1;
	if (opcode > e_invalid)
		opcode = e_invalid;
	return (opcode);
}
