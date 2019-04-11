#pragma once

#include <queue>

#include "Grid.h"
#include "Matrix.h"
#include "Piece.h"

class Game
{
public:
	Game();

// Tetris API functions
public:
	// ***** Model to View ****
	const Piece& GetCurrentPiece() const;

	const Matrix& GetGameBoard();

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

