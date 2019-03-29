/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   python_impl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:35:53 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/29 16:23:19 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "python_bindings.h"

void		py_game_dealloc(t_game_py_wrap *self)
{
	/* TODO call function to clear data */;
	free(self);
}

int		py_game_init(t_game_py_wrap *self, PyObject *Py_UNUSED(unused))
{
	self->data.state.log_info.log_mode = e_mode_save;
	array_init(&self->data.state.players, sizeof(t_player));
	self->champions = PyList_New(0);
	if (!self->champions)
		return (-1);
	Py_INCREF(self->champions);
	self->logs = PyTuple_New(e_log_level_max);
	if (!self->logs)
		return (-1);
	Py_INCREF(self->logs);
	self->memory = Py_None;
	Py_INCREF(Py_None);
	return (0);
}

PyObject	*py_update(t_game_py_wrap *self, PyObject *Py_UNUSED(unused))
{
	/*TODO*/
	(void)self;
	return (0);
}

static int	py_load_champions(t_array *players, PyObject *champion)
{
	const char	*name_string;
	PyObject	*ascii;
	t_player	new;

	if (!PyUnicode_Check(champion))
		return (-1);
	ascii = PyUnicode_AsASCIIString(champion);
	name_string = PyBytes_AsString(ascii);
	if (vm_champion_load_file(&new, name_string, -1 - players->length) < 0)
		return (-1);
	array_push_back(players, &new);
	return (0);
}

PyObject	*py_prepare(t_game_py_wrap *self, PyObject *Py_UNUSED(unused))
{
	size_t		index;
	size_t		list_size;
	t_array		players;
	t_log_info	log_opts;
	PyObject	*champion;
	int			is_list;

	is_list = PyList_Check(self->champions);
	if (is_list)
		list_size = PyList_Size(self->champions);
	if (!is_list || list_size < 1 || list_size > 4)
	{
		PyErr_SetString(PyExc_RuntimeError, "Champions should be a list of strings of size 1 to 4.");
		return (NULL);
	}
	index = 0;
	array_init(&players, sizeof(t_player));
	while (index < list_size)
	{
		champion = PyList_GetItem(self->champions, index);
		if (py_load_champions(&players, champion))
		{
			PyErr_SetString(PyExc_RuntimeError, "Champions should be a list of strings of size 1 to 4.");
			return (NULL);
		}
		index++;
	}
	logs_init(&log_opts);
	log_opts.log_mode = e_mode_save;
	prepare_game(&self->data, &players, &log_opts);
	Py_INCREF(Py_None);
	return (Py_None);
}
