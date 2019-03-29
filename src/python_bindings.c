/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   python_bindings.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamadori <aamadori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 19:01:57 by aamadori          #+#    #+#             */
/*   Updated: 2019/03/29 16:14:02 by aamadori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "python_bindings.h"
#include <structmember.h>

static PyMethodDef			g_module_methods[] = {
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef	g_corelib_module = {
	PyModuleDef_HEAD_INIT,
	"corelib",
	"Interface for the Corewars game",
	-1,
	g_module_methods
};

static PyMemberDef			g_py_game_members[] = {
	{"champions", T_OBJECT_EX, __offsetof(t_game_py_wrap, champions), READONLY, "List of champions to play"},
	{"logs", T_OBJECT_EX, __offsetof(t_game_py_wrap, logs), READONLY, "Tuple of logs"},
	{"memory", T_OBJECT_EX, __offsetof(t_game_py_wrap, memory), READONLY, "VM's memory"},
	{NULL, 0, 0, 0, NULL}
};

static PyMethodDef			g_py_game_methods[] = {
	{"update", (PyCFunction)py_update, METH_VARARGS, "Play n cycles of the game"},
	{"prepare", (PyCFunction)py_prepare, METH_NOARGS, "Prepares VM for match"},
	{NULL, NULL, 0, NULL}
};

static PyTypeObject			g_py_game = {
	PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "corelib.CorewarGame",
	.tp_doc = "Class used to handle a single Corewar match",
	.tp_basicsize = sizeof(t_game_py_wrap),
	.tp_itemsize = 0,
	.tp_flags = Py_TPFLAGS_DEFAULT,
	.tp_new = PyType_GenericNew,
	.tp_init = (initproc)py_game_init,
	.tp_dealloc = (destructor)py_game_dealloc,
	.tp_members = g_py_game_members,
	.tp_methods = g_py_game_methods
};

PyMODINIT_FUNC	PyInit_libcore(void)
{
	PyObject	*module;

	if (PyType_Ready(&g_py_game) < 0)
		return (NULL);
	module = PyModule_Create(&g_corelib_module);
	if (!module)
		return (NULL);
	PyModule_AddObject(module, "CorewarGame", (PyObject*)&g_py_game);
	Py_INCREF(&g_py_game);
	return (module);
}
