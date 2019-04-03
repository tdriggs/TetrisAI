#include "TetrisController.h"

TetrisController * TetrisController::Instance = nullptr;

TetrisController::TetrisController()
{
	this->game = new Game();
	this->TickTime = 1.0f;
	this->TickTimer = this->TickTime;
}

TetrisController::~TetrisController()
{
	delete this->game;
	delete this->Instance;
}

void TetrisController::TickController(float DeltaTime)
{
	this->TickTimer -= DeltaTime;
	if (this->TickTimer <= 0)
	{
		this->game->MovePieceDown();
		this->TickTimer = this->TickTime;
	}
}

const Matrix &TetrisController::GetGameBoard()
{
	return this->game->GetGameBoard();
}

const Piece & TetrisController::GetHeldPiece()
{
	return this->game->GetHeldPiece();
}

const std::queue<Piece> TetrisController::GetQueuedPieces()
{
	return this->game->GetQueuedPieces();
}

int TetrisController::GetScore()
{
	return 50;
}

void TetrisController::MovePieceRight()
{
	this->game->MovePieceRight();
}

void TetrisController::MovePieceLeft()
{
	this->game->MovePieceLeft();
}

void TetrisController::RotatePieceClockwise()
{
	this->game->RotatePieceClockwise();
}

void TetrisController::RotatePieceCounterClockwise()
{
	this->game->RotatePieceCounterClockwise();
}

void TetrisController::MovePieceDown()
{
	this->game->MovePieceDown();
}

void TetrisController::SwitchWithHeldPiece()
{
	this->game->SwitchWithHeldPiece();
}
