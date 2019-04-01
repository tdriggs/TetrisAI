#pragma once

class TetrisController
{
public:
	TetrisController();

public:
	// ***** Model to View *****

	void GetGameBoard();

	void GetHeldPiece();

	void GetQueuedPieces();

	// ***** View to Model *****

	void MovePieceRight();

	void MovePieceLeft();

	void RotatePieceClockwise();

	void RotatePieceCounterClockwise();

	void MovePieceDown();

	void SwitchWithHeldPiece();
};
