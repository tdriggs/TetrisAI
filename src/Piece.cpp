#include "Piece.h"

#include <array>

#include "PieceData.h"
#include "GridFrames.h"
#include "Grid.h"

Piece::Piece(PieceData::Type type, int row, int column, int frame)
	: m_type(type)
	, m_row(row)
	, m_column(column)
	, m_frame(frame)
{
}

void Piece::rotate(int frames)
{
	m_frame = (4 + (4 % (frames + m_frame))) % frames;
}

void Piece::move(int cells)
{
	m_column += cells;
}

void Piece::drop()
{
	m_row += 1;
}

PieceData::Type Piece::getType() const
{
	return m_type;
}

int Piece::getRow() const
{
	return m_row;
}

int Piece::getColumn() const
{
	return m_column;
}

const Grid<4, 4>& Piece::getGridFrame() const
{
	return s_piece_frames[static_cast<char>(m_type)][m_frame];
}

const std::array<GridFrames, 8> Piece::s_piece_frames =
{
	// VOID == 0
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
	}),

	// O == 1
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 1, 1, 0,
			0, 1, 1, 0,
			0, 0, 0, 0,
		}),
	}),

	// I == 2
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			2, 2, 2, 2,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 2, 0,
			0, 0, 2, 0,
			0, 0, 2, 0,
			0, 0, 2, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 0, 0, 0,
			2, 2, 2, 2,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 2, 0, 0,
			0, 2, 0, 0,
			0, 2, 0, 0,
			0, 2, 0, 0
		}),
	}),

	// T == 3
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			3, 3, 3, 0,
			0, 3, 0, 0,
			0, 0, 0, 0,
		}),
		Grid<4, 4>
		({
			0, 3, 0, 0,
			3, 3, 0, 0,
			0, 3, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 3, 0, 0,
			3, 3, 3, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 3, 0, 0,
			0, 3, 3, 0,
			0, 3, 0, 0,
			0, 0, 0, 0
		}),
	}),

	// S == 4
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 4, 4, 0,
			4, 4, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			4, 0, 0, 0,
			4, 4, 0, 0,
			0, 4, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			0, 4, 4, 0,
			4, 4, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			4, 0, 0, 0,
			4, 4, 0, 0,
			0, 4, 0, 0,
			0, 0, 0, 0
		}),
	}),

	// Z == 5
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			5, 5, 0, 0,
			0, 5, 5, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 5, 0,
			0, 5, 5, 0,
			0, 5, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 0, 0,
			5, 5, 0, 0,
			0, 5, 5, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 5, 0,
			0, 5, 5, 0,
			0, 5, 0, 0,
			0, 0, 0, 0
		}),
	}),

	// J == 6
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			6, 6, 6, 0,
			0, 0, 6, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 6, 0, 0,
			0, 6, 0, 0,
			6, 6, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			6, 0, 0, 0,
			6, 6, 6, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 6, 6, 0,
			0, 6, 0, 0,
			0, 6, 0, 0,
			0, 0, 0, 0
		}),
	}),

	// L == 7
	GridFrames
	({
		Grid<4, 4>
		({
			0, 0, 0, 0,
			7, 7, 7, 0,
			7, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			7, 7, 0, 0,
			0, 7, 0, 0,
			0, 7, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 0, 7, 0,
			7, 7, 7, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		}),
		Grid<4, 4>
		({
			0, 7, 0, 0,
			0, 7, 0, 0,
			0, 7, 7, 0,
			0, 0, 0, 0
		}),
	}),
};