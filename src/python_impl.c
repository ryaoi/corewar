/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   python_impl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:35:53 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/29 19:12:22 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "python_bindings.h"

void		py_game_dealloc(t_game_py_wrap *self)
{
	/* TODO call function to clear data */;
	free(self);
}

static int	py_init_logs(PyObject *logs)
{
	PyObject	*log_type;
	size_t		index;

	index = 0;
	while (index < e_log_level_max)
	{
		log_type = PyList_New(0);
		if (!log_type)
			return (-1);
		PyTuple_SET_ITEM(logs, index, log_type);
		index++;
	}
	return (0);
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
	if (py_init_logs(self->logs) < 0)
		return (-1);
	self->memory = Py_None;
	Py_INCREF(Py_None);
	return (0);
}

static int	py_append_log(PyObject *py_log, t_log_string *string)
{
	PyObject	*py_string;
	PyObject	*py_id;
	PyObject	*py_log_string;

	py_string = PyUnicode_FromString(string->string);
	if (!py_string)
		return (-1);
	py_id = PyLong_FromLong(string->id);
	if (!py_id)
		return (-1);
	py_log_string = PyTuple_New(2);
	if (!py_log_string)
		return (-1);
	PyTuple_SET_ITEM(py_log_string, 0, py_string);
	PyTuple_SET_ITEM(py_log_string, 1, py_id);
	if (PyList_Append(py_log, py_log_string) < 0)
		return (-1);
	return (0);
}

static int	py_save_logs(t_log_info	*info, PyObject *py_logs)
{
	enum e_log_level	log_level;
	t_log_string		*string;
	PyObject			*py_list;

	log_level = 0;
	while (log_level < e_log_level_max)
	{
		while (info->log_heads[log_level] < info->logs[log_level].length)
		{
			string = &ARRAY_PTR(info->logs[log_level], t_log_string)
				[info->log_heads[log_level]];
			py_list = PyTuple_GetItem(py_logs, log_level);
			if (!py_list || py_append_log(py_list, string) < 0)
				return (-1);
			info->log_heads[log_level]++;
		}
		log_level++;
	}
	return (0);
}

PyObject	*py_update(t_game_py_wrap *self, PyObject *Py_UNUSED(unused))
{
	/* TODO call prepare if not done yet */
	advance_cycle(&self->data);
	py_save_logs(&self->data.state.log_info, self->logs);
	Py_INCREF(Py_None);
	return (Py_None);
}

PyObject	*py_mem_dump(t_game_py_wrap *self, PyObject *Py_UNUSED(unused))
{
	PyObject *memory;

	memory = PyByteArray_FromStringAndSize((char*)self->data.state.memory, MEM_SIZE);
	if (!memory)
		return (NULL);
	Py_INCREF(memory);
	return (memory);
}

static int	py_load_champions(t_array *players, PyObject *champion)
{
	const char	*name_string;
	PyObject	*ascii;
	t_player	new;

	/* TODO get string representation of object */
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
