#include "PyTetrisFunctions.h"
#include "TetrisController.h"


PyObject * pyTetris_TickController(PyObject * self, PyObject * args)
{
	float DeltaTime;
	if (!(
		(PyTuple_Size(args) == 1 && PyArg_ParseTuple(args, "f", &DeltaTime))
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	CONTROLLER->TickController(DeltaTime);

	Py_RETURN_NONE;
}

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

PyObject * pyTetris_GetScore(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	return PyFloat_FromDouble(CONTROLLER->GetScore());
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

PyObject * pyTetris_SoftDrop(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	CONTROLLER->SoftDrop();

	Py_RETURN_NONE;
}

PyObject * pyTetris_ResetSoftDrop(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	CONTROLLER->ResetSoftDrop();

	Py_RETURN_NONE;
}

PyObject * pyTetris_HardDrop(PyObject * self, PyObject * args)
{
	if (!(
		(PyTuple_Size(args) == 0)
		))
	{
		PyErr_BadArgument();
		return NULL;
	}

	CONTROLLER->HardDrop();

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
