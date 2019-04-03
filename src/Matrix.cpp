#include "Matrix.h"


Matrix::Matrix()
{
}

Matrix::Matrix(const Matrix & matrix)
	:Grid(matrix.m_contents)
{

}

bool Matrix::overlaps(const Piece & piece) const
{
	return Grid::overlaps(piece.getGridFrame(), piece.getRow(), piece.getColumn());
}

void Matrix::place(const Piece &piece)
{
	const Grid<4, 4> &grid = piece.getGridFrame();

	for (int r = piece.getRow(); r < piece.getRow() + 4; ++r)
	{
		for(int c = piece.getColumn(); c < piece.getColumn() + 4; ++c)
		{
			Grid::set(r, c, piece.getType());
		}
	}
}