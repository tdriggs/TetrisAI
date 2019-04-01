#include "PyTetrisFunctions.h"
#include "TetrisController.h"

/*PyObject * tadPole::pyTadPole_loadScript(PyObject * self, PyObject * args)
{
	char * scriptName;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &scriptName))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	PYTHON_SCRIPT_MANAGER->executeScript(scriptName);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_log(PyObject * self, PyObject * args)
{
	char * message;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &message))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	LOG_MANAGER->log(message);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_saveScene(PyObject * self, PyObject * args)
{
	char * fileName;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &fileName))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	SCENE->save(fileName);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_loadScene(PyObject * self, PyObject * args)
{
	char * fileName;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &fileName))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	SCENE->load(fileName);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_clearScene(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	SCENE->clear();

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_createGroup(PyObject * self, PyObject * args)
{
	char * groupName;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &groupName))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	SCENE->createGroup(groupName);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_deleteGroup(PyObject * self, PyObject * args)
{
	char * groupName;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &groupName))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	SCENE->deleteGroup(groupName);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_setGroupActive(PyObject * self, PyObject * args)
{
	char * groupName;
	PyObject * activeObject;
	if (!(
		(PyTuple_Size(args) == 2 && PyArg_ParseTuple(args, "sO", &groupName, &activeObject))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}
	bool active = PyObject_IsTrue(activeObject);

	SCENE->setGroupActive(groupName, active);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_deleteGameObject(PyObject * self, PyObject * args)
{
	char * name;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &name))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	SCENE->deleteGameObject(name);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_getGroup(PyObject * self, PyObject * args)
{
	char * groupName;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &groupName))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	std::vector<GameObject *> group = SCENE->getGroup(groupName);
	PyObject * result = PyList_New(group.size());
	for (int i = 0; i < group.size(); ++i)
	{
		PyList_SetItem(result, i, (PyObject *)group.at(i)->getPyObject());
	}

	return result;
}

PyObject * tadPole::pyTadPole_getGameObject(PyObject * self, PyObject * args)
{
	char * name;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &name))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	GameObject * gameObject = SCENE->getGameObject(name);

	return (PyObject *)gameObject->getPyObject();
}

PyObject * tadPole::pyTadPole_registerEvent(PyObject * self, PyObject * args)
{
	char * eventType;
	char * triggerType;
	int option;
	if (!(
		(PyTuple_Size(args) == 3 && PyArg_ParseTuple(args, "ssi", &eventType, &triggerType, &option))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	INPUT_MANAGER->registerEventMapping(eventType, triggerType, option);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_deregisterEvent(PyObject * self, PyObject * args)
{
	char * eventType;
	char * triggerType;
	int option;
	if (!(
		(PyTuple_Size(args) == 3 && PyArg_ParseTuple(args, "ssi", &eventType, &triggerType, &option))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	INPUT_MANAGER->deregisterEventMapping(eventType, triggerType, option);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_clearMapping(PyObject * self, PyObject * args)
{
	char * eventType;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "s", &eventType))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	INPUT_MANAGER->clearMapping(eventType);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_captureMouse(PyObject * self, PyObject * args)
{
	bool * enabled;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "i", &enabled))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	INPUT_MANAGER->captureMouse(enabled);

	Py_RETURN_NONE;
}

PyObject * tadPole::pyTadPole_setAmbientLight(PyObject * self, PyObject * args)
{
	float r, g, b;;
	if (!(
		(PyTuple_Size(args) == 3 && PyArg_ParseTuple(args, "fff", &r, &g, &b))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	RENDER_MANAGER->setAmbientLight(glm::vec3(r, g, b));

	Py_RETURN_NONE;
}*/

PyObject * pyTetris_GetGameBoard(PyObject * self, PyObject * args)
{
	Py_RETURN_NONE;
}

PyObject * pyTetris_GetHeldPiece(PyObject * self, PyObject * args)
{
	Py_RETURN_NONE;
}

PyObject * pyTetris_GetQueuedPieces(PyObject * self, PyObject * args)
{
	Py_RETURN_NONE;
}

PyObject * pyTetris_MovePieceRight(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	CONTROLLER->MovePieceRight();

	Py_RETURN_NONE;
}

PyObject * pyTetris_MovePieceLeft(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	CONTROLLER->MovePieceLeft();

	Py_RETURN_NONE;
}

PyObject * pyTetris_RotatePieceClockwise(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	CONTROLLER->RotatePieceClockwise();

	Py_RETURN_NONE;
}

PyObject * pyTetris_RotatePieceCounterClockwise(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	CONTROLLER->RotatePieceCounterClockwise();

	Py_RETURN_NONE;
}

PyObject * pyTetris_MovePieceDown(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	CONTROLLER->MovePieceDown();

	Py_RETURN_NONE;
}

PyObject * pyTetris_SwitchWithHeldPiece(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	CONTROLLER->SwitchWithHeldPiece();

	Py_RETURN_NONE;
}
