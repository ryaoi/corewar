/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_unit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:16:51 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/20 15:22:52 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		arg_types_ocp(t_instr *instr, t_ocp ocp)
{
	int	arg_index;

	arg_index = 0;
	while (instr->opcode != e_invalid
		&& arg_index < g_opcode_table[instr->opcode].arg_num)
	{
		if (ocp.fields[arg_index] == e_register)
		{
			if (!(g_opcode_table[instr->opcode].arg_types[arg_index] & T_REG))
				instr->opcode = e_invalid;
			instr->instr_args[arg_index].arg_type = e_register;
		}
		else if (ocp.fields[arg_index] == e_index)
		{
			if (!(g_opcode_table[instr->opcode].arg_types[arg_index] & T_IND))
				instr->opcode = e_invalid;
			instr->instr_args[arg_index].arg_type = e_index;
		}
		else if (ocp.fields[arg_index] == e_direct)
		{
			if (!(g_opcode_table[instr->opcode].arg_types[arg_index] & T_DIR))
				instr->opcode = e_invalid;
			instr->instr_args[arg_index].arg_type = e_direct;
		}
		else
			instr->opcode = e_invalid;
		arg_index++;
	}
}

static void		arg_types_non_ocp(t_instr *instr)
{
	int	arg_index;

	arg_index = 0;
	while (arg_index < g_opcode_table[instr->opcode].arg_num)
	{
		if (g_opcode_table[instr->opcode].arg_types[arg_index] & T_REG)
			instr->instr_args[arg_index].arg_type = e_register;
		else if (g_opcode_table[instr->opcode].arg_types[arg_index] & T_IND)
			instr->instr_args[arg_index].arg_type = e_index;
		else
			instr->instr_args[arg_index].arg_type = e_direct;
		arg_index++;
	}
}

static size_t	parse_argument(t_vm_state *state, t_instr *instr,
					size_t argument, size_t address)
{
	t_bigend_buffer	load_arg;

	load_arg.buffer = 0;
	if (instr->instr_args[argument].arg_type == e_register)
	{
		/* TODO what to do if register index is higher than NUM_REG? */
		load_arg = mem_load(state, address + instr->size, 1);
		instr->instr_args[argument].arg.reg_index = ((uint8_t*)&load_arg.buffer)[7];
		return (1);
	}
	else if (instr->instr_args[argument].arg_type == e_index)
	{
		load_arg = mem_load(state, address + instr->size, IND_SIZE);
		instr->instr_args[argument].arg.index.content = load_arg;
		return (2);
	}
	else if (g_opcode_table[instr->opcode].relative)
	{
		load_arg = mem_load(state, address + instr->size, IND_SIZE);
		instr->instr_args[argument].arg.direct.content = load_arg;
		return (2);
	}
	load_arg = mem_load(state, address + instr->size, DIR_SIZE);
	instr->instr_args[argument].arg.direct.content = load_arg;
	return (4);
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
		ocp = parse_ocp(((uint8_t*)&load_buffer.buffer)[7]);
		arg_types_ocp(instr, ocp);
		instr->size++;
	}
	else
		arg_types_non_ocp(instr);
	arg_index = 0;
	while (instr->opcode != e_invalid
		&& arg_index < g_opcode_table[instr->opcode].arg_num)
	{
		instr->size += parse_argument(state, instr, arg_index, address);
		arg_index++;
	}
	if (instr->opcode != e_invalid)
		instr->is_jump = g_opcode_table[instr->opcode].is_jump;
}

t_instr		fetch_instruction(t_vm_state *state, size_t	address)
{
	size_t			match_index;
	t_bigend_buffer	opcode;
	t_instr			instr;

	match_index = 0;
	instr_init(&instr);
	opcode = mem_load(state, address, 1);
	instr.opcode = ((uint8_t*)&opcode.buffer)[7] - 1;
	while (match_index < sizeof(g_opcode_table)/sizeof(g_opcode_table[0]))
	{
		if (instr.opcode == g_opcode_table[match_index].opcode)
		{
			instr.size = 1;
			parse_instruction(state, &instr, address);
			return (instr);
		}
		match_index++;
	}
	instr.opcode = e_invalid;
	instr.size = 1;
	return (instr);
}
