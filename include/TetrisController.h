#pragma once

#include "Game.h"

#define CONTROLLER TetrisController::GetInstance()

class TetrisController
{
private:
	static TetrisController * Instance;
	
	Game* game;

	// ***** Singleton *****
public:
	TetrisController();

	~TetrisController();

	static TetrisController * GetInstance()
	{
		if (TetrisController::Instance == NULL)
		{
			TetrisController::Instance = new TetrisController();
		}
		return TetrisController::Instance;
	}


	// ***** Model to View *****
public:
	const Matrix &GetGameBoard();

	const Piece &GetHeldPiece();

	const std::queue<Piece> GetQueuedPieces();


	// ***** View to Model *****
public:
	void MovePieceRight();

	void MovePieceLeft();

	void RotatePieceClockwise();

	void RotatePieceCounterClockwise();

	void MovePieceDown();

	void SwitchWithHeldPiece();
};
