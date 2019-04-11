#include "Game.h"

#include <queue>

#include "PieceData.h"
#include "Serializer.h"

Game::Game()
	: m_currentPiece(PieceData::randomType())
	, m_heldPiece(PieceData::Void)
	, m_queuedPieces({ Piece(PieceData::randomType()) })
	, m_dropFrames(20)
	, m_currentFrame(0)
	, m_hasHeld(false)
{
}

const Piece& Game::GetCurrentPiece() const
{
	return this->m_currentPiece;
}

// ***** Model to View ****
const Matrix & Game::GetGameBoard()
{
	m_copy = m_matrix;
	m_copy.place(m_currentPiece);

	return m_copy;
}

const Piece & Game::GetHeldPiece() const
{
	return m_heldPiece;
}

const std::queue<Piece> Game::GetQueuedPieces() const
{
	return m_queuedPieces;
}

// ***** View to Model *****
void Game::MovePieceRight()
{	 
	m_currentPiece.move(1);

	if (m_matrix.overlaps(m_currentPiece))
	{
		m_currentPiece.move(-1);
	}
}	 
	 
void Game::MovePieceLeft()
{
	m_currentPiece.move(-1);

	if (m_matrix.overlaps(m_currentPiece))
	{
		m_currentPiece.move(1);
	}
}
	 
void Game::RotatePieceClockwise()
{
	m_currentPiece.rotate(1);

	if (m_matrix.overlaps(m_currentPiece))
	{
		m_currentPiece.rotate(-1);
	}
}
	 
void Game::RotatePieceCounterClockwise()
{
	m_currentPiece.rotate(-1);

	if (m_matrix.overlaps(m_currentPiece))
	{
		m_currentPiece.rotate(1);
	}
}
	 
bool Game::MovePieceDown()
{
	m_currentPiece.drop(1);

	if (m_matrix.overlaps(m_currentPiece))
	{
		SERIALIZER->RecordFrame(*this);  // Record this frame for training data collection

		m_hasHeld = false;
		m_currentPiece.drop(-1);

		m_matrix.place(m_currentPiece);
		m_matrix.clearLines();
		updateQueuedPieces();

		return true;
	}

	return false;
}
	 
void Game::SwitchWithHeldPiece()
{
	if (m_hasHeld) { return; }
	m_hasHeld = true;

	if (m_heldPiece.getType() == PieceData::Void)
	{
		m_heldPiece = Piece(m_currentPiece.getType());
		updateQueuedPieces();
	}
	else
	{
		PieceData::Type heldType = m_heldPiece.getType();
		m_heldPiece = Piece(m_currentPiece.getType());
		m_currentPiece = Piece(heldType);
	}
}

void Game::updateQueuedPieces()
{
	m_currentPiece = m_queuedPieces.front();
	m_queuedPieces.pop();
	m_queuedPieces.push(Piece(
		PieceData::randomType()
	));
}
