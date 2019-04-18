#include "Game.h"

#include <queue>
#include <iostream>

#include "PieceData.h"
#include "Serializer.h"

Game::Game()
	: m_currentPiece(PieceData::randomType(), SPAWN_ROW, SPAWN_COLUMN)
	, m_heldPiece(PieceData::Void)
	, m_queuedPieces({ Piece(PieceData::randomType(), SPAWN_ROW, SPAWN_COLUMN) })
	, m_dropFrames(20)
	, m_currentFrame(0)
	, m_hasHeld(false)
	, m_neuralNetwork(NUM_INPUTS, NUM_HIDDEN, NUM_OUTPUTS)
{
	for (int i = 0; i < 100; i++)
		;// m_neuralNetwork.train("..\\..\\training_data\\test.csv");
}

const Piece& Game::GetCurrentPiece() const
{
	return this->m_currentPiece;
}

const Piece& Game::GetCurrentGhostPiece() const
{
	Piece ghost = Piece(m_currentPiece);

	while (!m_matrix.overlaps(ghost))
	{
		ghost.drop(1);
	}

	return ghost;
}

// ***** Model to View ****
const Matrix & Game::GetGameBoard()
{
	m_copy = Matrix(m_matrix);
	m_copy.place(m_currentPiece);

	return m_copy;
}

const Matrix& Game::GetPlainGameBoard() const
{
	return m_matrix;
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
		m_hasHeld = false;
		m_currentPiece.drop(-1);

		SERIALIZER->RecordFrame(*this);  // Record this frame for training data collection

		m_matrix.place(m_currentPiece);
		m_matrix.clearLines();
		updateQueuedPieces();

		return true;
	}

	return false;
}
	 
void Game::SwitchWithHeldPiece()
{
	PlaceWithAI(); return;

	if (m_hasHeld) { return; }
	SERIALIZER->RecordFrame(*this, true);

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
		m_currentPiece = Piece(heldType, SPAWN_ROW, SPAWN_COLUMN);
	}
}

void Game::updateQueuedPieces()
{
	m_currentPiece = Piece(m_queuedPieces.front().getType(), SPAWN_ROW, SPAWN_COLUMN);
	m_queuedPieces.pop();
	m_queuedPieces.push(Piece(
		PieceData::randomType()
	));
}

Eigen::VectorXf Game::getInputVectorForNN()
{
	Eigen::VectorXf input = Eigen::VectorXf::Zero(221);

	int i = 0;
	for (PieceData::Type type : m_matrix.getContents())
	{
		input[i++] = (type == PieceData::Void) ? 0.0f : 1.0f;
	}

	int currType = m_currentPiece.getType();
	int nextType = m_queuedPieces.front().getType();
	int heldType = m_heldPiece.getType();

	input[200 + currType - 1] = 1.0f;
	input[207 + nextType - 1] = 1.0f;

	if (heldType != 0)
		input[214 + heldType - 1] = 1.0f;

	return input;
}

int Game::getHighestRow()
{
	for (int r = 0; r < m_matrix.HEIGHT; r++)
	{
		for (int c = 0; c < m_matrix.WIDTH; c++)
		{
			if (m_matrix.get(r, c) != PieceData::Void)
			{
				return r;
			}
		}
	}

	return 20;
}

Piece Game::getPieceFromNN(int largest)
{
	int classification = m_neuralNetwork.classify(getInputVectorForNN());

	if (classification == NUM_OUTPUTS - 1)
	{
		return Piece(PieceData::Void);
	}

	int mini_matrix_size = OUTPUT_DEPTH * m_matrix.WIDTH;
	int classification_no_frame = ((classification - 1) % mini_matrix_size);

	int frame = (classification - 1) / mini_matrix_size;
	Piece tempPiece = Piece(m_currentPiece.getType(), 0, 0, frame);
	std::pair<int, int> offset = tempPiece.getOffset();

	int relative_row = classification_no_frame / m_matrix.WIDTH - offset.first;
	int col = classification_no_frame % m_matrix.WIDTH - offset.second;

	int row = relative_row + getHighestRow();

	if (row > 20 - offset.first)
		row = 20 - offset.first;

	if (row < 0)
		row = 0;

	std::cout << row << ", " << col << std::endl;

	return Piece(m_currentPiece.getType(), row, col, frame);
}

void Game::PlaceWithAI()
{
	Piece piece = getPieceFromNN(0);
	int edge = piece.getRightEdge();

	if (edge >= m_matrix.WIDTH) {
		piece.move(m_matrix.WIDTH - edge - 1);
	}

	m_currentPiece = piece;

	while (m_matrix.overlaps(m_currentPiece) && m_currentPiece.getRow() >= 0)
	{
		m_currentPiece.drop(-1);
	}

	while (!MovePieceDown())
		;

	return;
}
