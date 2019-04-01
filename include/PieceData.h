#pragma once

namespace PieceData
{
	enum Type
	{
		Void = 0,
		O = 1,
		I = 2,
		T = 3,
		S = 4,
		Z = 5,
		J = 6,
		L = 7
	};

	Type randomType();
};