/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   python_impl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 14:35:53 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/31 17:43:39 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "python_bindings.h"

void		py_game_dealloc(t_game_py_wrap *self)
{
	if (self->ready)
		vm_state_clear(&self->data.state);
	Py_DECREF(self->champions);
	self->champions = NULL;
	Py_DECREF(self->logs);
	self->logs = NULL;
	Py_TYPE(self)->tp_free(self);
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

int		py_game_init(t_game_py_wrap *self, PyObject *Py_UNUSED(unused1),
			PyObject *Py_UNUSED(unused2))
{
	self->data.state.log_info.log_mode = e_mode_save;
	array_init(&self->data.state.players, sizeof(t_player));
	self->champions = PyList_New(0);
	if (!self->champions)
		return (-1);
	self->logs = PyTuple_New(e_log_level_max);
	if (!self->logs)
		return (-1);
	if (py_init_logs(self->logs) < 0)
		return (-1);
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
	Py_DECREF(py_log_string);
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
	PyObject	*err;
	PyObject	*py_game_cont;
	int			game_cont;

	/* TODO what happens when game is over? */
	if (!self->ready)
	{
		err = PyObject_CallMethod(self, "prepare", NULL);
		if (!err)
			return (NULL);
		Py_DECREF(err);
		err = NULL;
	}
	game_cont = advance_cycle(&self->data);
	py_save_logs(&self->data.state.log_info, self->logs);
	if (game_cont)
	{
		Py_INCREF(Py_True);
		return (Py_True);
	}
	Py_INCREF(Py_False);
	return (Py_False);
}

PyObject	*py_mem_dump(t_game_py_wrap *self, PyObject *Py_UNUSED(unused))
{
	PyObject *memory;

	memory = PyByteArray_FromStringAndSize((char*)self->data.state.memory, MEM_SIZE);
	if (!memory)
		return (NULL);
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
	Py_DECREF(ascii);
	ascii = NULL;
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

	if (self->ready)
	{
		PyErr_SetString(PyExc_RuntimeError, "Class is only meant to be used for one match. To restart, create another instance.");
		return (NULL);
	}
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
	self->ready = 1;
	return (Py_None);
}

static int	py_player_set_properties(PyObject *dict, t_player *player)
{
	PyObject	*property;

	property = PyUnicode_FromString(player->header.prog_name);
	if (!property || PyDict_SetItemString(dict, "name", property) < 0)
		return (-1);
	property = PyUnicode_FromString(player->header.comment);
	if (!property || PyDict_SetItemString(dict, "comment", property) < 0)
		return (-1);
	property = PyLong_FromUnsignedLong(player->header.prog_size);
	if (!property || PyDict_SetItemString(dict, "size", property) < 0)
		return (-1);
	property = PyLong_FromLong(player->id);
	if (!property || PyDict_SetItemString(dict, "id", property) < 0)
		return (-1);
	property = PyLong_FromLong(player->live);
	if (!property || PyDict_SetItemString(dict, "live", property) < 0)
		return (-1);
	return (0);
}

PyObject	*py_players(t_game_py_wrap *self, PyObject *Py_UNUSED(unused))
{
	PyObject	*list;
	PyObject	*player;
	int			ret;
	size_t		index;

	list = PyList_New(self->data.state.players.length);
	if (!list)
		return (NULL);
	index = 0;
	while (index < self->data.state.players.length)
	{
		player = PyDict_New();
		if (!player)
			return (NULL);
		ret = py_player_set_properties(player,
			&ARRAY_PTR(self->data.state.players, t_player)[index]);
		if (ret < 0 || PyList_SetItem(list, index, player) < 0)
			return (NULL);
		index++;
	}
	return (list);
}

static int	py_process_set_registers(PyObject *dict, t_process *process)
{
	PyObject	*tuple;
	PyObject	*value;
	size_t		index;

	tuple = PyTuple_New(REG_NUMBER);
	if (!tuple)
		return (-1);
	index = 0;
	while (index < REG_NUMBER)
	{
		value = PyLong_FromSize_t(process->registers[index].content.buffer);
		if (!value || PyTuple_SetItem(tuple, index, value) < 0)
			return (-1);
		index++;
	}
	if (PyDict_SetItemString(dict, "registers", tuple) < 0)
		return (-1);
	return (0);
}

static int	py_process_set_properties(PyObject *dict, t_process *process)
{
	PyObject	*property;

	if (py_process_set_registers(dict, process) < 0)
		return (-1);
	property = PyLong_FromLong(process->player->id);
	if (!property || PyDict_SetItemString(dict, "player_id", property) < 0)
		return (-1);
	property = PyLong_FromSize_t(process->program_counter);
	if (!property || PyDict_SetItemString(dict, "program_counter", property) < 0)
		return (-1);
	property = PyLong_FromSize_t(process->id);
	if (!property || PyDict_SetItemString(dict, "process_id", property) < 0)
		return (-1);
	property = PyLong_FromSize_t(process->live_executed);
	if (!property || PyDict_SetItemString(dict, "lives_since_check", property) < 0)
		return (-1);
	property = PyLong_FromUnsignedLong(process->has_jumped);
	if (!property || PyDict_SetItemString(dict, "has_jumped", property) < 0)
		return (-1);
	property = PyLong_FromLong(process->carry);
	if (!property || PyDict_SetItemString(dict, "carry", property) < 0)
		return (-1);
	property = PyLong_FromLong(process->busy);
	if (!property || PyDict_SetItemString(dict, "busy", property) < 0)
		return (-1);
	property = PyLong_FromSize_t(process->birth_cycle);
	if (!property || PyDict_SetItemString(dict, "birth_cycle", property) < 0)
		return (-1);
	return (0);
}

PyObject	*py_processes(t_game_py_wrap *self, PyObject *Py_UNUSED(unused))
{
	PyObject	*list;
	PyObject	*process;
	t_list		*traverse;
	int			ret;

	list = PyList_New(0);
	if (!list)
		return (NULL);
	traverse = self->data.state.processes;
	while (traverse)
	{
		process = PyDict_New();
		if (!process)
			return (NULL);
		ret = py_process_set_properties(process,
			&LST_CONT(traverse, t_process));
		if (ret < 0 || PyList_Append(list, process) < 0)
			return (NULL);
		Py_DECREF(process);
		traverse = traverse->next;
	}
	if (PyList_Reverse(list) < 0)
		return (NULL);
	return (list);
}
