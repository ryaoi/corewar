/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:01:53 by jaelee            #+#    #+#             */
/*   Updated: 2019/03/17 01:48:25 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	free_token_content(void *content, size_t size)
{
	t_token		*tmp;

	(void)size;
	tmp = (t_token*)content;
	if (tmp->str)
		free(tmp->str);
	if (tmp->op)
		free(tmp->op);
	tmp->str = NULL;
	tmp->op = NULL;
	free(tmp);
}

void	free_line_content(void *content, size_t size)
{
	t_line	*tmp;

	(void)size;
	tmp = (t_line*)content;
	if (tmp->str)
		free(tmp->str);
	tmp->str = NULL;
	if (tmp->tokens)
		list_del(&tmp->tokens, free_token_content);
	free(tmp);
	tmp = NULL;
}

void	file_error(const char *str, t_file *file)
{
	if (file->name_s)
		free(file->name_s);
	if (file->name_cor)
		free(file->name_cor);
	list_del(&(file->lines), free_line_content);
	if (str)
		ft_putendl(str);
	exit(EXIT_FAILURE);
}
