#include "GridFrames.h"

#include <array>

#include "Grid.h"

GridFrames::GridFrames(std::array<Grid<4, 4>, 4> data)
	:m_frames(data)
{
}

const Grid<4, 4>& GridFrames::operator[](int index) const
{
	if (index < 0 || index >= 4)
	{
		index = (4 + (index % 4)) % 4; // True Modulo to make it cyclic
	}

	return m_frames[index];
}