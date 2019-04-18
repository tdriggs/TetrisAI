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
	m_frame = (4 + ((frames + m_frame) % 4)) % 4;
}

void Piece::move(int cells)
{
	m_column += cells;
}

void Piece::drop(int cells)
{
	m_row += cells;
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

int Piece::getFrameIndex() const
{
	return m_frame;
}

int Piece::getRightEdge() const
{
	for (int c = 3; c >=0 ; c--)
	{
		for (int r = 0; r < 4; r++)
		{
			if (getGridFrame().get(r, c) != PieceData::Void)
			{
				return m_column + c;
			}
		}
	}

	return m_column;
}

const std::pair<int, int> & Piece::getOffset()
{
	return s_piece_offsets[m_type - 1][m_frame];
}

const Grid<4, 4>& Piece::getGridFrame() const
{
	return s_piece_frames[static_cast<char>(m_type)][m_frame];
}

const std::array<std::array<std::pair<int, int>, 4>, 7> Piece::s_piece_offsets =
{
	//O
	std::array<std::pair<int, int>, 4>
	{
		std::pair<int, int>{2, 1},
		std::pair<int, int>{2, 1},
		std::pair<int, int>{2, 1},
		std::pair<int, int>{2, 1}
	},
	//I
	std::array<std::pair<int, int>, 4>
	{
		std::pair<int, int>{1, 0},
		std::pair<int, int>{3, 2},
		std::pair<int, int>{2, 0},
		std::pair<int, int>{0, 1}
	},
	//T
	std::array<std::pair<int, int>, 4>
	{
		std::pair<int, int>{2, 0},
		std::pair<int, int>{2, 0},
		std::pair<int, int>{1, 0},
		std::pair<int, int>{2, 1}
	},
	//S
	std::array<std::pair<int, int>, 4>
	{
		std::pair<int, int>{2, 0},
		std::pair<int, int>{2, 0},
		std::pair<int, int>{2, 0},
		std::pair<int, int>{2, 0}
	},
	//Z
	std::array<std::pair<int, int>, 4>
	{
		std::pair<int, int>{2, 0},
		std::pair<int, int>{2, 1},
		std::pair<int, int>{2, 0},
		std::pair<int, int>{2, 1}
	},
	//J
	std::array<std::pair<int, int>, 4>
	{
		std::pair<int, int>{2, 0},
		std::pair<int, int>{2, 0},
		std::pair<int, int>{1, 0},
		std::pair<int, int>{2, 1}
	},
	//L
	std::array<std::pair<int, int>, 4>
	{
		std::pair<int, int>{2, 0},
		std::pair<int, int>{2, 0},
		std::pair<int, int>{1, 0},
		std::pair<int, int>{2, 1}
	}
};

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