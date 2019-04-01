#pragma once

#include "Python.h"

PyObject * pyTetris_GetGameBoard(PyObject * self, PyObject * args);

PyObject * pyTetris_GetHeldPiece(PyObject * self, PyObject * args);

PyObject * pyTetris_GetQueuedPieces(PyObject * self, PyObject * args);

PyObject * pyTetris_MovePieceRight(PyObject * self, PyObject * args);

PyObject * pyTetris_MovePieceLeft(PyObject * self, PyObject * args);

PyObject * pyTetris_RotatePieceClockwise(PyObject * self, PyObject * args);

PyObject * pyTetris_RotatePieceCounterClockwise(PyObject * self, PyObject * args);

PyObject * pyTetris_MovePieceDown(PyObject * self, PyObject * args);

PyObject * pyTetris_SwitchWithHeldPiece(PyObject * self, PyObject * args);
