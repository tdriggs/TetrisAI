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

	for (int r = 0; r < grid.HEIGHT; ++r)
	{
		for(int c = 0; c < grid.WIDTH; ++c)
		{
			PieceData::Type type = piece.getGridFrame().get(r, c);
			
			if (type != PieceData::Void)
			{
				Grid::set(r + piece.getRow(), c + piece.getColumn(), type);
			}
		}
	}
}

int Matrix::clearLines()
{
	int linesCleared = 0;

	for (int r = HEIGHT-1; r >= 0; --r)
	{

		if (isLineFull(r))
		{
			linesCleared += 1;
		}
		else
		{
			copyLines(r, r + linesCleared);
		}
	}

	return linesCleared;
}

bool Matrix::isLineFull(int row) const
{
	for (int c = 0; c < WIDTH; ++c)
	{
		if (this->get(row, c) == PieceData::Void)
		{
			return false;
		}
	}

	return true;
}

void Matrix::copyLines(int from, int to)
{
	if (from == to ||
		from < 0 || from >= HEIGHT ||
		to < 0 || to >= HEIGHT)
	{
		return;
	}

	for (int c = 0; c < WIDTH; ++c)
	{
		set(to, c, get(from, c));
	}
}