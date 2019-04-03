#include "TetrisController.h"

#include <iostream>

int main()
{
	Matrix m = CONTROLLER->GetGameBoard();

	std::cout << m.get(0, 0);

	return 0;
}
