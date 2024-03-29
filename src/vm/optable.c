/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optable.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:04:58 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/19 20:08:08 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

const t_op	g_opcode_table[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, 0},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, 0},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, 0},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0, 0}
};

const t_instr_impl		g_impl_table[17] =
{
	impl_live,
	impl_ld,
	impl_st,
	impl_add,
	impl_sub,
	/*impl_and,
	impl_or,
	impl_xor,*/
	NULL,
	NULL,
	NULL,
	impl_zjmp,
	impl_ldi,
	impl_sti,
	impl_fork,
	impl_lld,
	impl_lldi,
	impl_lfork,
	impl_aff
};
