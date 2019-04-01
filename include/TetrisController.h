#pragma once

#define CONTROLLER TetrisController::GetInstance()

class TetrisController
{
private:
	static TetrisController * Instance;


	// ***** Singleton *****
public:
	TetrisController();

	~TetrisController();

	static TetrisController * GetInstance()
	{
		return TetrisController::Instance;
	}


	// ***** Model to View *****
public:
	void GetGameBoard();

	void GetHeldPiece();

	void GetQueuedPieces();


	// ***** View to Model *****
public:
	void MovePieceRight();

	void MovePieceLeft();

	void RotatePieceClockwise();

	void RotatePieceCounterClockwise();

	void MovePieceDown();

	void SwitchWithHeldPiece();
};
