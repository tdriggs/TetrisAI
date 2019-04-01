#include "PieceData.h"

#include <stdlib.h>

PieceData::Type PieceData::randomType()
{
	return Type((rand() % 7) + 1);
}
