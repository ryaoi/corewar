/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:36:38 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/15 16:38:59 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CPU_H
# define _CPU_H
# include "vm.h"

enum	e_instr_arg_type
{
	e_register = 0,
	e_index,
	e_direct
};

enum	e_instr
{
	e_live = 0,
	e_ld,
	e_st,
	e_add,
	e_sub,
	e_and,
	e_or,
	e_xor,
	e_zjmp,
	e_ldi,
	e_sti,
	e_fork,
	e_lld,
	e_lldi,
	e_lfork,
	e_aff,
	e_invalid
};

typedef struct		s_op
{
	const char		*name;
	int				arg_num;
	const int		*arg_types;
	enum e_instr	opcode;
	int				cycles;
	const char		*explanation;
	uint8_t			has_ocp;
	uint8_t			relative;
}					t_op;

typedef struct		s_register
{
	uint8_t		content[REG_SIZE];
}					t_register;

typedef struct		s_direct
{
	uint8_t		relative;
	size_t		value;
}					t_direct;

typedef struct		s_instr_arg
{
	enum e_instr_arg_type	arg_type;
	union
	{
		size_t		reg_index;
		size_t		index;
		t_direct	direct;
	}							arg;
}					t_instr_arg;

typedef struct 		s_instr
{
	enum e_instr	opcode;
	t_instr_arg		instr_args[3];
	size_t			size;
}					t_instr;

typedef t_instr		(*t_instr_parser)(t_vm_state *, size_t);
t_instr				parser_live(t_vm_state *state, size_t address);
t_instr				parser_ld(t_vm_state *state, size_t address);
t_instr				parser_st(t_vm_state *state, size_t address);
t_instr				parser_add(t_vm_state *state, size_t address);
t_instr				parser_sub(t_vm_state *state, size_t address);
t_instr				parser_and(t_vm_state *state, size_t address);
t_instr				parser_or(t_vm_state *state, size_t address);
t_instr				parser_xor(t_vm_state *state, size_t address);
t_instr				parser_zjmp(t_vm_state *state, size_t address);
t_instr				parser_ldi(t_vm_state *state, size_t address);
t_instr				parser_sti(t_vm_state *state, size_t address);
t_instr				parser_fork(t_vm_state *state, size_t address);
t_instr				parser_lld(t_vm_state *state, size_t address);
t_instr				parser_lldi(t_vm_state *state, size_t address);
t_instr				parser_lfork(t_vm_state *state, size_t address);
t_instr				parser_aff(t_vm_state *state, size_t address);

typedef void		(*t_instr_impl)(t_vm_state *, t_process *);
void				impl_live(t_vm_state *state, t_process *process);
void				impl_ld(t_vm_state *state, t_process *process);
void				impl_st(t_vm_state *state, t_process *process);
void				impl_add(t_vm_state *state, t_process *process);
void				impl_sub(t_vm_state *state, t_process *process);
void				impl_and(t_vm_state *state, t_process *process);
void				impl_or(t_vm_state *state, t_process *process);
void				impl_xor(t_vm_state *state, t_process *process);
void				impl_zjmp(t_vm_state *state, t_process *process);
void				impl_ldi(t_vm_state *state, t_process *process);
void				impl_sti(t_vm_state *state, t_process *process);
void				impl_fork(t_vm_state *state, t_process *process);
void				impl_lld(t_vm_state *state, t_process *process);
void				impl_lldi(t_vm_state *state, t_process *process);
void				impl_lfork(t_vm_state *state, t_process *process);
void				impl_aff(t_vm_state *state, t_process *process);

t_instr				fetch_instruction(t_vm_state *state, size_t	address);

extern const t_op			g_opcode_table[17];
extern const t_instr_parser	g_parser_table[17];
extern const t_instr_impl	g_impl_table[17];

#endif
