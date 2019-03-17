/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:17:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/17 00:06:15 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "list.h"
# include "op.h"
# include "ft_printf.h"
# define TOKEN_SYNTAX_ERROR 0
# define SUCCESS 1
# define ASM_FAIL 0
# define LINE_FAIL 0
# define TOKEN_FAIL 0
# define REGISTER_CHAR 'r'

typedef enum e_token_types
{
	T_NAME, /* .name */
	T_CMD_COMMENT, /* .comment */
	T_COMMENT, /* # */
	T_LABEL, /* T_STRING + ':' */

	T_INSTR, /* instructions */

	T_REGISTER, /* 'r' + T_INTEGER */
	T_DIRECT, /* '%' + T_INTEGER */
	T_INDIRECT, /* ?? */
	T_DIRLAB, /* '%:' + T_LABEL */
	T_INDIRLAB, /* ':' + T_LABEL */

	T_ASMCODE, /* instructions + params */
	T_UNKNOWN
}			t_token_types;

# define TOKEN ((t_token*)(traverse->content))
# define LINE ((t_line*)(traverse->content))
# define ERROR(msg, ret) {ft_putendl(msg);return(ret);}

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
	char				*bytecode;
	size_t				pos;

}				t_line;

typedef struct	s_file
{
	t_list		*lines; /* maybe t_array is better? */
	size_t		nbr_line;
	char		*name_s;
	char		*name_cor;
	header_t	header; /* TODO initialize header!! */
	int			fd_cor;
	int			fd_s;
	int			ret;
}				t_file;

void	file_error(const char *str, t_file *file);
void	read_file(t_file *file);
int		add_token(t_line *line, int token_id, int start, int end);
int		parse_file(t_file *file);
int		tokenize_line(t_line *line);
int		add_token(t_line *line, int token_id, int start, int end);
int		check_token_type(t_token *token, char *str);
int		check_parameter(t_token *token, char *str);
int		validate_opcode_params(t_line *line);
int		is_str_digit(char *str);
int		is_comment(t_line *line);
int		is_whitespaces_line(const char *str);

#endif
