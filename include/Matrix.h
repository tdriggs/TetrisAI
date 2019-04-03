#pragma once

#include "Grid.h"
#include "Piece.h"

class Matrix :
	public Grid<10, 20>
{
public:
	Matrix();
	Matrix(const Matrix & matrix);

	bool overlaps(const Piece &piece) const;
	void place(const Piece &piece);
};

