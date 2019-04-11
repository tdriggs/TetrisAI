#pragma once

#include "Python.h"

PyObject * pyTetris_TickController(PyObject * self, PyObject * args);

PyObject * pyTetris_GetGameBoard(PyObject * self, PyObject * args);

PyObject * pyTetris_GetHeldPiece(PyObject * self, PyObject * args);

PyObject * pyTetris_GetQueuedPieces(PyObject * self, PyObject * args);

PyObject * pyTetris_GetScore(PyObject * self, PyObject * args);

PyObject * pyTetris_MovePieceRight(PyObject * self, PyObject * args);

PyObject * pyTetris_MovePieceLeft(PyObject * self, PyObject * args);

PyObject * pyTetris_RotatePieceClockwise(PyObject * self, PyObject * args);

PyObject * pyTetris_RotatePieceCounterClockwise(PyObject * self, PyObject * args);

PyObject * pyTetris_SoftDrop(PyObject * self, PyObject * args);

PyObject * pyTetris_ResetSoftDrop(PyObject * self, PyObject * args);

PyObject * pyTetris_HardDrop(PyObject * self, PyObject * args);

PyObject* pyTetris_SwitchWithHeldPiece(PyObject* self, PyObject* args);

PyObject* pyTetris_Quit(PyObject* self, PyObject* args);
