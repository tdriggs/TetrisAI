#include "TetrisController.h"

TetrisController * TetrisController::Instance = nullptr;

TetrisController::TetrisController()
{
	this->game = new Game();
}

TetrisController::~TetrisController()
{
	delete this->game;
	delete this->Instance;
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
