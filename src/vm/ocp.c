/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:15:38 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/26 14:47:24 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_ocp	parse_ocp(uint8_t byte)
{
	size_t	index;
	uint8_t	field;
	t_ocp	ocp;

	ft_bzero(&ocp, sizeof(t_ocp));
	index = 0;
	while (index < 3)
	{
		field = (byte >> ((index + 1) * 2)) & 0b11;
		if (field == 0b00)
			ocp.fields[(3 - 1) - index] = e_absent;
		else if (field == 0b01)
			ocp.fields[(3 - 1) - index] = e_register;
		else if (field == 0b10)
			ocp.fields[(3 - 1) - index] = e_direct;
		else
			ocp.fields[(3 - 1) - index] = e_index;
		index++;
	}
	return (ocp);
}

void		arg_types_ocp(t_instr *instr, t_ocp ocp)
{
	int	arg_index;

	arg_index = 0;
	while (arg_index < g_opcode_table[instr->opcode].arg_num)
	{
		if (ocp.fields[arg_index] == e_register)
		{
			if (!(g_opcode_table[instr->opcode].arg_types[arg_index] & T_REG))
				instr->invalid = 1;
			instr->instr_args[arg_index].arg_type = e_register;
		}
		else if (ocp.fields[arg_index] == e_index)
		{
			if (!(g_opcode_table[instr->opcode].arg_types[arg_index] & T_IND))
				instr->invalid = 1;
			instr->instr_args[arg_index].arg_type = e_index;
		}
		else if (ocp.fields[arg_index] == e_direct)
		{
			if (!(g_opcode_table[instr->opcode].arg_types[arg_index] & T_DIR))
				instr->invalid = 1;
			instr->instr_args[arg_index].arg_type = e_direct;
		}
		else
		{
			instr->instr_args[arg_index].arg_type = e_absent;
			instr->invalid = 1;
		}
		arg_index++;
	}
}

void		arg_types_non_ocp(t_instr *instr)
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
