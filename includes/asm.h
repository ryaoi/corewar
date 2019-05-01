/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:17:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/05/01 14:16:55 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "list.h"
# include "op.h"
# include "ft_printf.h"

# define SUCCESS 1
# define FAIL 0
# define FILE_ERROR 0
/*
# define FAIL 0
# define FILE_ERROR 0
# define ASM_FAIL 0
# define LINE_FAIL 0
# define TOKEN_FAIL 0
# define PARAM_CHECK_FAIL 0
# define INSTR_FAIL 0
# define PARAM_FAIL 0
# define OPCODE_CMP_FAIL 0
# define GETVALUE_FAIL -1
# define CONVERSION_FAIL 0
*/
# define ON 1
# define OFF 0
# define REGISTER_CHAR 'r'

# define REG_INDEX_SIZE 1
# define DIR_D2_SIZE 2
# define DIR_D4_SIZE 4
# define INDIR_SIZE 2

# define PREWORK_FLAG_ON 0b11

extern t_op	g_op_tab[17];

typedef enum e_token_types
{
	T_NAME_CMD, /* .name WHITE_SPACES "strings"*/
	T_COMMENT_CMD, /* .comment WHITE_SPACES "strings"*/
	T_COMMENT, /* # + string */
	T_LABEL, /* string + ':' */
	T_ASMCODE, /* instructions + params must relates to a T_LABEL */
	T_INSTR, /* instructions */
	T_REGISTER = 11, /* 'r' + T_INTEGER */
	T_DIRECT = 12, /* '%' + T_INTEGER */
	T_INDIRECT = 14, /* T_INTEGER */
	T_DIRLAB = 15, /* '%:' + T_LABEL */
	T_INDIRLAB = 16, /* ':' + T_LABEL */
	T_UNKNOWN /* added to handle other than labels later */
}			t_token_types;

typedef enum	e_err_types
{
	/* libft / malloc fail */
	STRDUP_FAIL = -50,
	STRNDUP_FAIL,
	STRJOIN_FAIL,
	STRTRIM_FAIL,
	MALLOC_FAIL,
	STRSUB_FAIL,
	GNL_FAIL,
/* file error */
	DOT_S_ERROR,
	OPEN_FILE_ERROR,
/* main error */
	FILE_READ_FAIL,
	FILE_PARSE_FAIL,
	FILE_UNKNOWN_HEADER,
	FILE_CONVERSION_FAIL,
/* file read error */
	CONTENT_EMPTY,
	LINE_CREATE_FAIL,
	HANDLE_CMT_FAIL,
/* file parse error */
	TOKENIZER_FAIL,
	OPCOMDE_CMP_FAIL,
	HEADER_NOT_FOUND,
/* token error */
	TOKEN_TOO_MANY,
	TOKEN_TYPE_FAIL,
	TOKEN_LABEL_SYNTAX_FAIL,
	TOKEN_REGISTER_FAIL,
	TOKEN_TYPE_UNKNOWN,
	TOKEN_INSTR_INVALID,
/* opcode compare error */
	PARAM_OP_NOT_EXIST,
	PARAM_NBR_FAIL,
	PARAM_NOT_EXIST,
	PARAM_NOT_VALID,
/* file_conversion error */
	OPERATION_NOT_EXIST,
	PARAMS_NOT_EXIST,
	LABEL_NOT_EXIST,

	CREATE_FILE_FAIL,
}				t_err_types;

typedef struct	s_token
{
	t_op				*op;
	char				*str;
	size_t				id;
	int					type;
	int					value;
}				t_token;

typedef struct	s_line
{
	char				*str;
	size_t				id;
	int					type;
	int					nbr_params;
	t_list				*tokens;
	unsigned char		*bytecode;
	size_t				pos;
	unsigned int		bytecode_len;

}				t_line;

typedef struct	s_file
{
	t_list		*lines; /* maybe t_array is better? */
	size_t		nbr_line;
	char		*name_s;
	char		*name_cor;
	int			prework_flag;
	header_t	header; /* TODO initialize header!! */
	int			fd_cor;
	int			fd_s;
	int			ret;
}				t_file;


/*
** main.c
*/
void	assemble_file(t_list *traverse);
void	file_add(t_list **inputs, char *filename);

/*
** file_utils.c
*/
void	file_init(t_file *file);
int		file_name_check(const char *filename, t_file *file);
int		argv_check(int argc);
void	file_next(t_list **files, t_file *file);
/*
** file_read.c
*/
int		file_read(t_file *file);
void	handle_comment(t_file *file, char *line);
int		line_add(t_file *file, char *line, size_t label_pos);
int		line_create(t_file *file, char *line, int line_type);

/*
** file_read_utils.c
*/
int		line_is_ws(const char *str);
size_t	label_check(char *line);
int		read_error(t_file *file);

/*
** file_parse.c
*/
int		file_parse(t_file *file);
int		tokenize_line(t_line *line);
int		opcode_cmp(t_line *line);
int		check_parameter(t_token *token, char *str);
int		validate_opcode_params(t_line *line);

/*
** file_parse_utils.c
*/
int		is_str_digit(char *str);
int		is_comment(t_line *line);
void	init_token(t_token *token);
void	remove_label_char(char *str);

/*
** file_parse_check.c
*/
int		check_token_type(t_token *token, char *str);
int		check_label_syntax(char *str);
int		check_register(char *str);
int		check_instr(t_token *token, char *str);

/*
** bytecode_length.c
*/
void	get_bytecode_len(t_line *line);

/*
** file_parse_tokenizer.c
*/
int		line_tokenize(t_line *line);
void	get_token(char *str, int *i, int *j, int token_id);
int		add_token(t_line *line, int token_id, char *str);

/*
** file_parse_header.c
*/
void	set_header(t_file *file, t_line *line);

/*
** file_conversion.c
*/
int		file_conversion(t_file *file);
t_op	*operation_set(t_line *line);
int		bc_translation(t_file *file, t_line *line, t_list *traverse, t_op *op);

/*
** bytecode_translation.c
*/
void	param_trans(unsigned char *bytecode, int size, int *bc_index,
						int value);
int		param_getvalue(t_list *lines, t_line *line, t_token *token);


int		write_cor_file(t_file *file);

/*
** print_errors.c
*/
void	print_errmsg_file(int err_type, char *filename);
void	print_errmsg_file_read(int err_type);
void	print_errmsg_tokenizer(int err_type, char *line);
void	print_errmsg_opcode_cmp(int err_type, char *line);
void	print_errmsg_conversion(int err_type, char *line);

/*
** ft_exit.c
*/
void	free_asm(t_list *inputs);
/*TODO duplicate labels handling!!!! */
#endif
