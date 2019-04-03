#include "PyTetrisFunctions.h"
#include "TetrisController.h"


/*
glm::vec3 position = self->gameObject->getLocalPosition();
PyObject * result = PyTuple_New(3);

PyTuple_SetItem(result, 0, PyFloat_FromDouble(position.x));
PyTuple_SetItem(result, 1, PyFloat_FromDouble(position.y));
PyTuple_SetItem(result, 2, PyFloat_FromDouble(position.z));
*/


PyObject * pyTetris_GetGameBoard(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	Matrix board = CONTROLLER->GetGameBoard();

	PyObject * result = PyTuple_New(20);
	for (int i = 0; i < 20; ++i)
	{
		PyObject * row = PyTuple_New(10);

		for (int j = 0; j < 10; ++j)
		{
			PyTuple_SetItem(row, j, PyFloat_FromDouble(board.get(i, j)));
		}

		PyTuple_SetItem(result, i, row);
	}

	return result;
}

PyObject * pyTetris_GetHeldPiece(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	Piece held = CONTROLLER->GetHeldPiece();
	Grid<4, 4> frame = held.getGridFrame();

	PyObject * result = PyTuple_New(4);
	for (int i = 0; i < 4; ++i)
	{
		PyObject * row = PyTuple_New(4);

		for (int j = 0; j < 4; ++j)
		{
			PyTuple_SetItem(row, j, PyFloat_FromDouble(frame.get(i, j)));
		}

		PyTuple_SetItem(result, i, row);
	}

	return result;
}

PyObject * pyTetris_GetQueuedPieces(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	std::queue<Piece> queued = CONTROLLER->GetQueuedPieces();
	PyObject * result = PyTuple_New(queued.size());

	int index = 0;
	while (!queued.empty())
	{
		PyObject * pyPiece = PyTuple_New(4);

		Piece piece = queued.front();
		queued.pop();
		Grid<4, 4> frame = piece.getGridFrame();

		for (int i = 0; i < 4; ++i)
		{
			PyObject * row = PyTuple_New(4);

			for (int j = 0; j < 4; ++j)
			{
				PyTuple_SetItem(row, j, PyFloat_FromDouble(frame.get(i, j)));
			}

			PyTuple_SetItem(pyPiece, i, row);
		}

		PyTuple_SetItem(result, index, pyPiece);
		++index;
	}

	return result;
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
