#pragma once

#include <array>

#include "GridFrames.h"
#include "PieceData.h"

class Piece
{
public:
	static const std::array<GridFrames, 8> s_piece_frames;

public:
	Piece(PieceData::Type type, int row=0, int column=0, int frame=0);

	void rotate(int frames);
	void move(int cells);
	void drop();

	PieceData::Type getType() const;
	int getRow() const;
	int getColumn() const;
	const Grid<4, 4>& getGridFrame() const;

private:
	 PieceData::Type m_type;
	 int m_row, m_column, m_frame;
};

