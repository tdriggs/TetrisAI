#include "TetrisController.h"

#include <iostream>

int main()
{
	CONTROLLER->RotatePieceClockwise();
	CONTROLLER->SwitchWithHeldPiece();
	CONTROLLER->HardDrop();

	return 0;
}
