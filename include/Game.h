#pragma once

#include <queue>

#include "Grid.h"
#include "Matrix.h"
#include "Piece.h"

class Game
{
public:
		static const int SPAWN_COLUMN = 3;
		static const int SPAWN_ROW = 0;

public:
	Game();

// Tetris API functions
public:
	// ***** Model to View ****
	const Piece& GetCurrentPiece() const;

	const Piece& GetCurrentGhostPiece() const;

	const Matrix& GetGameBoard();

	const Matrix& GetPlainGameBoard() const;

	const Piece & GetHeldPiece() const;

	const std::queue<Piece> GetQueuedPieces() const;

	// ***** View to Model *****
	void MovePieceRight();

	void MovePieceLeft();

	void RotatePieceClockwise();

	void RotatePieceCounterClockwise();

	bool MovePieceDown();

	void SwitchWithHeldPiece();

private:
	void updateQueuedPieces();

private:
	Matrix m_matrix, m_copy;
	Piece m_currentPiece, m_heldPiece;
	std::queue<Piece> m_queuedPieces;

	int m_dropFrames, m_currentFrame;

	bool m_hasHeld;
};

