/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2019/03/16 15:45:33 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _VM_H
# define _VM_H
# include <stdint.h>
# include <sys/types.h>
# include "array.h"
# include "cpu.h"

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

typedef struct		s_header
{
	uint32_t		magic;
  	char			prog_name[PROG_NAME_LENGTH + 1];
	uint32_t		prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_process
{
	t_register	registers[REG_NUMBER];
	t_header	header;
	size_t		program_counter;
	int			carry;
	size_t		id;
	int			live;
	int			busy;
	t_instr		pending_operation;
}					t_process;

typedef struct		s_vm_state
{
	t_array		processes;
	size_t		cycle_count;
	uint8_t		memory[MEM_SIZE];
}					t_vm_state;

t_bigend_buffer	mem_load(t_vm_state *state, size_t address, size_t size);
void			mem_store(t_vm_state *state, size_t address, size_t size,
					const t_bigend_buffer store);
t_bigend_buffer	byte_order_swap(t_bigend_buffer input, size_t size);

#endif
