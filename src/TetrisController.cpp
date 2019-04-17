#include "TetrisController.h"
#include "Serializer.h"

TetrisController * TetrisController::Instance = nullptr;

TetrisController::TetrisController()
{
	this->game = new Game();
	this->TickTime = 1.5f;
	this->TickTimer = this->TickTime;
	this->SoftDropTime = 0.1f;
	this->SoftDropTimer = 0;
	this->ShouldSoftDrop = true;
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
		if (!this->ShouldSoftDrop)
		{
			this->game->MovePieceDown();
		}
		this->TickTimer = this->TickTime;
	}

	if (this->ShouldSoftDrop)
	{
		this->SoftDropTimer -= DeltaTime;
		if (this->SoftDropTimer <= 0)
		{
			this->game->MovePieceDown();
			this->ShouldSoftDrop = false;
			this->SoftDropTimer = this->SoftDropTime;
		}
	}
}

void TetrisController::Quit()
{
	SERIALIZER->Quit();
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

void TetrisController::SoftDrop()
{
	this->ShouldSoftDrop = true;
}

void TetrisController::ResetSoftDrop()
{
	this->ShouldSoftDrop = false;
	this->SoftDropTimer = 0.0f;
}

void TetrisController::HardDrop()
{
	while (!this->game->MovePieceDown())
		;
}

void TetrisController::SwitchWithHeldPiece()
{
	this->game->SwitchWithHeldPiece();
}
