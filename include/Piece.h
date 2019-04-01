#pragma once

#include <array>

#include "GridFrames.h"
#include "PieceData.h"

class Piece
{
public:
	static const std::array<GridFrames, 8> s_piece_frames;

public:
	Piece(PieceData::Type type, int row, int column);

	const Grid<4, 4>& getGridFrame();

private:
	 PieceData::Type m_type;
	 int m_row, m_column, m_frame;
};

