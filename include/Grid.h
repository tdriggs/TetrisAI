#pragma once

#include <vector>
#include <memory>
#include <array>

#include "PieceData.h"

template<int W, int H>
class Grid
{
public:
	const static int WIDTH = W;
	const static int HEIGHT = H;

	Grid()
	{
	}

	Grid(const std::array<char, W*H>& contents)
	{
		// Couldn't find a better way than this, static_cast<std::array<PieceData::Type, W*H>>(contents) doesn't work
		for (int i = 0; i < W*H; ++i)
		{
			m_contents[i] = static_cast<PieceData::Type>(contents[i]);
		}
	}

	Grid(std::array<PieceData::Type, W*H> contents)
		:m_contents(contents)
	{
	};

	inline PieceData::Type get(int row, int col) const
	{
		if (row < 0 || row >= H ||
			col < 0 || col >= W)
		{
			return PieceData::Type::O;
		}

		return m_contents[W*row + col];
	}
	
	inline void set(int row, int col, PieceData::Type type)
	{
		if (row < 0 || row >= H ||
			col < 0 || col >= W)
		{
			return;
		}

		m_contents[W*row + col] = type;
	}

	template<int ww, int hh> bool overlaps(const Grid<ww, hh> &grid, int row, int column) const
	{
		for (int r = 0; r < hh; ++r)
		{
			for (int c = 0; c < ww; ++c)
			{
				if (this->get(r + row, c + column) != PieceData::Type::Void 
					&& grid.get(r, c) != PieceData::Type::Void)
				{
					return true;
				}
			}
		}

		return false;
	}

	const std::array<PieceData::Type, W*H> & getContents()
	{
		return m_contents;
	}

protected:
	std::array<PieceData::Type, W*H> m_contents;
};

