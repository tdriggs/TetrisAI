#pragma once

#include <array>

#include "Grid.h"

class GridFrames
{
public:
	GridFrames(std::array<Grid<4, 4>, 4> data);

	const Grid<4, 4>& operator[](int index) const;
private:
	std::array<Grid<4, 4>, 4> m_frames;
};

