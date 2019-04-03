#include "TetrisController.h"

#include <iostream>

int main()
{
	CONTROLLER->MovePieceDown();
	CONTROLLER->MovePieceDown();
	CONTROLLER->MovePieceDown();
	CONTROLLER->MovePieceDown();
	CONTROLLER->MovePieceDown();
	CONTROLLER->MovePieceDown();
	CONTROLLER->MovePieceDown();
	CONTROLLER->MovePieceDown();
	CONTROLLER->SwitchWithHeldPiece();
	Matrix m = CONTROLLER->GetGameBoard();
	Piece p = CONTROLLER->GetHeldPiece();
	Grid<4, 4> g = p.getGridFrame();

	std::cout << m.get(0, 0);
	std::cout << g.get(0, 0);

	return 0;
}
