#include "TetrisController.h"

TetrisController * TetrisController::Instance = nullptr;

TetrisController::TetrisController()
{
	if (this->Instance == nullptr)
	{
		this->Instance = this;
	}
}

TetrisController::~TetrisController()
{
	delete this->Instance;
}

void TetrisController::GetGameBoard()
{
}

void TetrisController::GetHeldPiece()
{
}

void TetrisController::GetQueuedPieces()
{
}

void TetrisController::MovePieceRight()
{
}

void TetrisController::MovePieceLeft()
{
}

void TetrisController::RotatePieceClockwise()
{
}

void TetrisController::RotatePieceCounterClockwise()
{
}

void TetrisController::MovePieceDown()
{
}

void TetrisController::SwitchWithHeldPiece()
{
}
