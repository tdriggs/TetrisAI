#include "Matrix.h"


Matrix::Matrix()
{
}

bool Matrix::overlaps(const Piece & piece) const
{
	return Grid::overlaps(piece.getGridFrame(), piece.getRow(), piece.getColumn());
}

void Matrix::place(const Piece &piece)
{
	const Grid<4, 4> &grid = piece.getGridFrame();

	for (int r = piece.getRow(); r < 4; ++r)
	{
		for(int c = piece.getColumn(); c < 4; ++c)
		{
			Grid::set(r, c, piece.getType());
		}
	}
}