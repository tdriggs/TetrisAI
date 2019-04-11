#include "pyTetrisModule.h"
#include "pyTetrisFunctions.h"


PyMethodDef pyTetrisModuleFunctions[] =
{
	{ "tick", pyTetris_TickController, METH_VARARGS, "" },
	{ "get_game_board", pyTetris_GetGameBoard, METH_VARARGS, "" },
	{ "get_held_piece", pyTetris_GetHeldPiece, METH_VARARGS, "" },
	{ "get_queued_pieces", pyTetris_GetQueuedPieces, METH_VARARGS, "" },
	{ "get_score", pyTetris_GetScore, METH_VARARGS, "" },
	{ "move_piece_right", pyTetris_MovePieceRight, METH_VARARGS, "" },
	{ "move_piece_left", pyTetris_MovePieceLeft, METH_VARARGS, "" },
	{ "rotate_piece_clockwise", pyTetris_RotatePieceClockwise, METH_VARARGS, "" },
	{ "rotate_piece_counter_clockwise", pyTetris_RotatePieceCounterClockwise, METH_VARARGS, "" },
	{ "soft_drop", pyTetris_SoftDrop, METH_VARARGS, "" },
	{ "reset_soft_drop", pyTetris_ResetSoftDrop, METH_VARARGS, "" },
	{ "hard_drop", pyTetris_HardDrop, METH_VARARGS, "" },
	{ "switch_with_held_piece", pyTetris_SwitchWithHeldPiece, METH_VARARGS, "" },
	{ "quit", pyTetris_Quit, METH_VARARGS, "" },
	{ NULL, NULL, 0, NULL }
};

struct PyModuleDef pyTetrisModule =
{
	PyModuleDef_HEAD_INIT,
	"pyTetris",
	"A tetris control and model module.",
	-1,
	pyTetrisModuleFunctions
};

PyMODINIT_FUNC PyInit_pyTetris()
{
	PyObject * module = PyModule_Create(&(pyTetrisModule));
	if (module == NULL)
	{
		return NULL;
	}

	return module;
}
