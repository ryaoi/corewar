/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:17:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/06/05 13:57:23 by pmorgan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "list.h"
# include "vm.h"
# include "ft_printf.h"

# define FT_SUCCESS 1
# define FT_FAIL 0

# define ON 1
# define OFF 0
# define REGISTER_CHAR 'r'

# define REG_INDEX_SIZE 1
# define DIR_D2_SIZE 2
# define DIR_D4_SIZE 4
# define INDIR_SIZE 2

# define PREWORK_FLAG_ON 0b11

extern const t_op	g_op_tab[17];

typedef enum	e_token_types
{
	e_name_cmd = 0,
	e_comment_cmd,
	e_comment,
	e_label,
	e_asmcode,
	e_instr,
	e_reg = 11,
	e_dir = 12,
	e_indir = 14,
	e_dirlab,
	e_indirlab,
	e_unknown
}				t_token_types;

typedef enum	e_err_types
{
	e_strdup_fail = -29,
	e_strndup_fail,
	e_strjoin_fail,
	e_strtrim_fail,
	e_malloc_fail,
	e_strsub_fail,
	e_gnl_fail,
	e_cmd_line_error,
	e_dot_s_error,
	e_open_file_error,
	e_file_parse_fail,
	e_file_conversion_fail,
	e_content_empty,
	e_line_create_fail,
	e_header_not_found,
	e_token_too_many,
	e_token_type_fail,
	e_token_label_syntax_fail,
	e_token_register_fail,
	e_token_type_unknwon,
	e_token_instr_invalid,
	e_param_op_not_exist,
	e_param_nbr_fail,
	e_param_not_exist,
	e_param_not_valid,
	e_operation_not_exist,
	e_conv_params_not_exist,
	e_label_not_exist,
	e_create_file_fail,
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
	t_list		*lines;
	size_t		nbr_line;
	char		*name_s;
	char		*name_cor;
	int			prework_flag;
	t_header	header;
	int			fd_cor;
	int			fd_s;
	int			ret;
}				t_file;

/*
** main.c
*/
void			assemble_file(t_list *traverse);
void			file_add(t_list **inputs, char *filename);

/*
** file_utils.c
*/
void			file_init(t_file *file);
int				file_name_check(const char *filename, t_file *file);
int				argv_check(int argc);
void			file_next(t_list **files, t_file *file);
/*
** file_read.c
*/
int				file_read(t_file *file);
void			handle_comment(char *line);
int				line_add(t_file *file, char *line, size_t label_pos);
int				line_create(t_file *file, char *line, int line_type);

/*
** file_read_utils.c
*/
int				line_is_ws(const char *str);
size_t			label_check(char *line);
int				read_error(t_file *file);

/*
** file_parse.c
*/
int				file_parse(t_file *file);
int				tokenize_line(t_line *line);
int				opcode_cmp(t_line *line);
int				check_parameter(t_token *token, char *str);
int				validate_opcode_params(t_line *line);

/*
** file_parse_utils.c
*/
int				is_str_digit(char *str);
void			init_token(t_token *token);
void			remove_label_char(char *str);

/*
** file_parse_check.c
*/
int				check_token_type(t_token *token, char *str);
int				check_label_syntax(char *str);
int				check_register(char *str);
int				check_instr(t_token *token, char *str);

/*
** bytecode_length.c
*/
void			get_bytecode_len(t_line *line);

/*
** file_parse_tokenizer.c
*/
int				line_tokenize(t_line *line);
void			get_token(char *str, int *i, int *j, int token_id);
int				add_token(t_line *line, int token_id, char *str);

/*
** file_parse_header.c
*/
void			set_header(t_file *file, t_line *line);

/*
** file_conversion.c
*/
int				file_conversion(t_file *file);
t_op			*operation_set(t_line *line);
int				bc_translation(t_file *file, t_line *line, t_list *traverse,
					t_op *op);

/*
** bytecode_translation.c
*/
void			param_trans(unsigned char *bytecode, int size, int *bc_index,
					int value);
int				param_getvalue(t_list *lines, t_line *line, t_token *token);
int				write_cor_file(t_file *file);

/*
** print_errors.c
*/
void			print_errmsg_file(int err_type, char *filename);
void			print_errmsg_file_read(int err_type);
void			print_errmsg_tokenizer(int err_type, char *line);
void			print_errmsg_opcode_cmp(int err_type, char *line);
void			print_errmsg_conversion(int err_type, char *line);

/*
** ft_exit.c
*/
void			free_asm(t_list *inputs);

#endif
