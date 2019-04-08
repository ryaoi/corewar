/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 22:01:53 by jaelee            #+#    #+#             */
/*   Updated: 2019/04/08 15:39:42 by jaelee           ###   ########.fr       */
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
	if (tmp->bytecode)
		free(tmp->bytecode);
	tmp->bytecode = NULL;
	if (tmp->tokens)
		list_del(&tmp->tokens, free_token_content);
	free(tmp);
	tmp = NULL;
}

void	free_file_content(void *content, size_t size)
{
	t_file	*tmp;

	(void)size;
	tmp = (t_file*)content;
	if (tmp->name_s)
		free(tmp->name_s);
	tmp->name_s = NULL;
	if (tmp->name_cor)
		free(tmp->name_cor);
	tmp->name_cor = NULL;
	list_del(&(tmp->lines), free_line_content);
	free(tmp);
}

void	free_asm(t_list *inputs)
{
	list_del(&inputs, free_file_content);
}
