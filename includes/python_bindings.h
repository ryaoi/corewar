/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   python_bindings.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:02:25 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 15:46:06 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PYTHON_BINDINGS_H
# define _PYTHON_BINDINGS_H
#include <Python.h>
#include <structmember.h>
#include "game.h"

typedef struct	s_game_py_wrap
{
	PyObject_HEAD
	t_game_data	data;
	PyObject	*champions;
	PyObject	*logs;
	size_t		py_curr_cycle;
	uint8_t		ready;
}				t_game_py_wrap;

void		py_game_dealloc(t_game_py_wrap *self);
int			py_game_init(t_game_py_wrap *self, PyObject *Py_UNUSED(unused1),
				PyObject *Py_UNUSED(unused2));
PyObject	*py_mem_dump(t_game_py_wrap *self, PyObject *Py_UNUSED(unused));
PyObject	*py_update(t_game_py_wrap *self, PyObject *Py_UNUSED(unused));
PyObject	*py_prepare(t_game_py_wrap *self, PyObject *Py_UNUSED(unused));
PyObject	*py_players(t_game_py_wrap *self, PyObject *Py_UNUSED(unused));
PyObject	*py_processes(t_game_py_wrap *self, PyObject *Py_UNUSED(unused));

#endif
