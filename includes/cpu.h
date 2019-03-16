/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:36:38 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/16 15:40:07 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CPU_H
# define _CPU_H

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_NUMBER				16

# include <sys/types.h>
# include <stdint.h>

enum	e_instr_arg_type
{
	e_register = 0,
	e_index,
	e_direct,
	e_absent
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

typedef struct		s_bigend_buffer
{
	/* TODO max buffer size? asserts? */
	uint8_t		buffer[8];
}					t_bigend_buffer;

typedef struct		s_register
{
	t_bigend_buffer	content;
}					t_register;

typedef struct		s_direct
{
	uint8_t			relative;
	t_bigend_buffer	content;
}					t_direct;

typedef struct		s_index
{
	t_bigend_buffer	content;
}					t_index;

typedef struct		s_instr_arg
{
	enum e_instr_arg_type	arg_type;
	union
	{
		uint8_t		reg_index;
		t_index		index;
		t_direct	direct;
	}							arg;
}					t_instr_arg;

typedef struct 		s_instr
{
	enum e_instr	opcode;
	t_instr_arg		instr_args[3];
	size_t			size;
}					t_instr;

typedef struct		s_ocp
{
	enum e_instr_arg_type	fields[3];
}					t_ocp;


typedef void		(*t_instr_impl)(t_vm_state *, t_process *, t_instr *);
void				impl_live(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_ld(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_st(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_add(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_sub(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_and(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_or(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_xor(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_zjmp(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_ldi(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_sti(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_fork(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_lld(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_lldi(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_lfork(t_vm_state *state,
						t_process *process, t_instr *instr);
void				impl_aff(t_vm_state *state,
						t_process *process, t_instr *instr);

t_instr				fetch_instruction(t_vm_state *state, size_t	address);
void				parse_arguments(t_vm_state *state, t_instr *instr,
						size_t address);
t_ocp				parse_ocp(uint8_t byte);
void				instr_init(t_instr *instr);
int					buffer_is_zero(t_bigend_buffer buffer, size_t size);
void				buffer_invert_bits(t_bigend_buffer buffer, size_t size);

extern const t_op			g_opcode_table[17];
extern const t_instr_impl	g_impl_table[17];

#endif
