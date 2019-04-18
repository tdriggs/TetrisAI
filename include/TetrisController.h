#pragma once

#include <time.h>
#include <stdlib.h>

#include "Game.h"

#define CONTROLLER TetrisController::GetInstance()

class TetrisController
{
private:
	static TetrisController * Instance;
	
	Game* game;

	float TickTime;
	float TickTimer;
	float SoftDropTime;
	float SoftDropTimer;
	bool ShouldSoftDrop;

	// ***** Singleton *****
public:
	TetrisController();

	~TetrisController();

	static TetrisController * GetInstance()
	{
		if (TetrisController::Instance == NULL)
		{
			srand(static_cast<unsigned int>(time(0)));
			TetrisController::Instance = new TetrisController();
		}
		return TetrisController::Instance;
	}

	// ***** View To Controller *****
public:
	void TickController(float DeltaTime);

	void Quit();


	// ***** Model to View *****
public:
	const Matrix &GetGameBoard();

	const Piece &GetHeldPiece();

	const std::queue<Piece> GetQueuedPieces();

	int GetScore();


	// ***** View to Model *****
public:
	void MovePieceRight();

	void MovePieceLeft();

	void RotatePieceClockwise();

	void RotatePieceCounterClockwise();

	void SoftDrop();

	void ResetSoftDrop();

	void HardDrop();

	void SwitchWithHeldPiece();
};
