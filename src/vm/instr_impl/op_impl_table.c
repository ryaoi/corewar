/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_impl_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 11:21:34 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/25 11:23:26 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

const t_instr_impl		g_impl_table[17] =
{
	impl_live,
	impl_ld,
	impl_st,
	impl_add,
	impl_sub,
	impl_and,
	impl_or,
	impl_xor,
	impl_zjmp,
	impl_ldi,
	impl_sti,
	impl_fork,
	impl_lld,
	impl_lldi,
	impl_lfork,
	impl_aff
};
