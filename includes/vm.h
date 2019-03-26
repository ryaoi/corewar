/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/03/26 12:37:01 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VM_H
# define _VM_H
# include <stdint.h>
# include <sys/types.h>
# include "array.h"
# include "list.h"
#include "ft_printf.h" /* TODO remove */

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_NUMBER				16

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

# define ERR_FILE -1
# define ERR_HEADER_READ -2
# define ERR_CHAMP_TOO_LARGE -3
# define ERR_CHAMP_READ -4

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

typedef struct		s_header
{
	uint32_t		magic;
  	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_player
{
	t_header	header;
	uint8_t		*champion_code;
	int			id;
	int			live;
}					t_player;

typedef struct		s_bigend_buffer
{
	/* TODO max buffer size? asserts? */
	size_t		buffer;
}					t_bigend_buffer;

typedef struct		s_register
{
	t_bigend_buffer	content;
}					t_register;

typedef struct		s_direct
{
	/* uint8_t			relative; */
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
	uint8_t			invalid;
	size_t			cost;
	size_t			size;
}					t_instr;

typedef struct		s_process
{
	t_register	registers[REG_NUMBER];
	t_player	*player;
	size_t		program_counter;
	int			carry;
	int			busy;
	uint8_t		has_jumped;
	size_t		live_executed;
	size_t		id;
	size_t		birth_cycle;
	enum e_instr	pending_operation;
}					t_process;

typedef struct		s_vm_state
{
	t_list		*processes;
	t_array		players;
	size_t		process_count;
	size_t		cycle_count;
	uint8_t		memory[MEM_SIZE];
}					t_vm_state;

typedef struct		s_op
{
	const char		*name;
	int				arg_num;
	const int		arg_types[3];
	enum e_instr	opcode;
	int				cycles;
	const char		*explanation;
	uint8_t			has_ocp;
	uint8_t			relative;
	uint8_t			is_jump;
}					t_op;

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

t_instr		fetch_arguments(t_vm_state *state, enum e_instr opcode, size_t address);
enum e_instr	fetch_opcode(t_vm_state *state, size_t address);
void				parse_arguments(t_vm_state *state, t_instr *instr,
						size_t address);
t_ocp				parse_ocp(uint8_t byte);
void				instr_init(t_instr *instr);
int					buffer_is_zero(t_bigend_buffer buffer);
t_bigend_buffer		buffer_invert_bits(t_bigend_buffer input);
t_bigend_buffer		add_bigend(t_bigend_buffer f, t_bigend_buffer s, uint8_t carry);
t_bigend_buffer	mem_load(t_vm_state *state, int64_t address, size_t size);
void			mem_store(t_vm_state *state, int64_t address, size_t size,
					const t_bigend_buffer store);
t_bigend_buffer	byte_order_swap(t_bigend_buffer input);
void			vm_clone_process(t_vm_state *state, size_t address, t_process *original);
void			vm_init_process(t_vm_state *state, int player_id, size_t address);
void			vm_state_init(t_vm_state *state);
int				vm_champion_load_file(t_player *player, const char *filename, int id);
int				vm_champion_load(t_player *player, int fd, int id);
void			vm_memory_prepare(t_vm_state *state);
int				vm_exec_cycle(t_vm_state *state);
int				play_game(t_array *players, t_vm_state **final, size_t max_cycles);
void			dump_memory(t_vm_state *state);

extern const t_op			g_opcode_table[17];
extern const t_instr_impl	g_impl_table[17];

#endif
