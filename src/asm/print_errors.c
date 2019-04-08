/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:54:11 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 22:50:16 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_errmsg_file(int err_type, char *filename)
{
	if (err_type == DOT_S_ERROR)
		ft_putendl("the filename has to exist and ends with '.s'");
	else if (err_type == OPEN_FILE_ERROR)
		ft_printf("failed to open '%s'. Check if '%s' is existing file.\n",
						filename, filename);
	else if (err_type == STRDUP_FAIL)
		ft_putendl("ft_strdup failed.");
	else if (err_type == STRNDUP_FAIL)
		ft_putendl("ft_strndup failed.");
	else if (err_type == STRJOIN_FAIL)
		ft_putendl("ft_strjoin failed.");
}

void	print_errmsg_file_read(int err_type)
{
	if (err_type == GNL_FAIL)
		ft_putendl("get_next_line() failed.");
	else if (err_type == CONTENT_EMPTY)
		ft_putendl("content of the file is empty.");
}

void	print_errmsg_tokenizer(int err_type, char *line)
{
	if (err_type == STRSUB_FAIL)
		ft_printf("ft_strsub failed.");
	if (err_type == MALLOC_FAIL)
		ft_putendl("malloc failed.");
	else if (err_type == TOKEN_TYPE_FAIL)
		ft_printf("at '%s'\ntoken_type error.\n", line);
	else if (err_type == TOKEN_LABEL_SYNTAX_FAIL)
		ft_printf("at '%s'\nlabel syntax error.\n", line);
	else if (err_type == TOKEN_REGISTER_FAIL)
		ft_printf("at '%s'\nregister number too high.\n", line);
	else if (err_type == TOKEN_TYPE_UNKNOWN)
		ft_printf("at '%s'\ntoken_type not found.\n", line);
	else if (err_type == TOKEN_INSTR_INVALID)
		ft_printf("at '%s'\nno opcode match found.\n", line);
}

void	print_errmsg_opcode_cmp(int err_type, char *line)
{
	if (err_type == PARAM_OP_NOT_EXIST)
		ft_printf("at '%s'\ntoken doesn't exists in this line.\n", line);
	else if (err_type == PARAM_NBR_FAIL)
		ft_printf("at '%s'\nnumber of parameters is not valid.\n", line);
	else if (err_type == PARAM_NOT_EXIST)
		ft_printf("at '%s'\nparameter doesn't exist.\n", line);
	else if (err_type == PARAM_NOT_VALID)
		ft_printf("at '%s'\nnot valid param according to \
					the op_table.\n", line);
}

void	print_errmsg_conversion(int err_type, char *line)
{
	if (err_type == OPERATION_NOT_EXIST)
		ft_printf("at '%s'\noperation doesn't exist.\n", line);
	else if (err_type == PARAMS_NOT_EXIST)
		ft_printf("at '%s'\nparameter doesn't exist.\n", line);
	else if (err_type == LABEL_NOT_EXIST)
		ft_printf("at '%s'\nlabel doesn't exist.\n", line);
}
