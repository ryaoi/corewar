/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_short.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 17:19:56 by aamadori          #+#    #+#             */
/*   Updated: 2019/05/27 18:21:33 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint8_t		*arg_reg(t_instr *instr, size_t id)
{
	return (&(instr->instr_args[id].arg.reg_index));
}

t_index		*arg_ind(t_instr *instr, size_t id)
{
	return (&(instr->instr_args[id].arg.index));
}

t_direct	*arg_dir(t_instr *instr, size_t id)
{
	return (&(instr->instr_args[id].arg.direct));
}

t_arg_type	*arg_type(t_instr *instr, size_t id)
{
	return (&(instr->instr_args[id].arg_type));
}
