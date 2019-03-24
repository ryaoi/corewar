/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:17:09 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/24 15:44:42 by jaelee           ###   ########.fr       */
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
# define PARAM_FAIL 0
# define CONVERSION_FAIL 0
# define ON 1
# define OFF 0
# define REGISTER_CHAR 'r'
# define REGISTER_INDEX_SIZE 1
# define DIRECT_D2_SIZE 2
# define DIRECT_D4_SIZE 4
# define INDIRECT_SIZE 2

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
	unsigned char		*bytecode;
	size_t				pos;
	size_t				bytecode_len;

}				t_line;

typedef struct	s_file
{
	t_list		*lines; /* maybe t_array is better? */
	size_t		nbr_line;
	char		*name_s;
	char		*name_cor;
	int			header_flags;
	header_t	header; /* TODO initialize header!! */
	int			fd_cor;
	int			fd_s;
	int			ret;
}				t_file;

void	file_error(const char *str, t_file *file);
void	file_read(t_file *file);
int		file_parse(t_file *file);
int		file_conversion(t_file *file);
int		add_token(t_line *line, int token_id, int start, int end);
int		tokenize_line(t_line *line);
int		add_token(t_line *line, int token_id, int start, int end);
int		check_token_type(t_token *token, char *str);
int		check_parameter(t_token *token, char *str);
int		validate_opcode_params(t_line *line);
int		is_str_digit(char *str);
int		is_comment(t_line *line);
int		is_whitespaces_line(const char *str);

#endif
