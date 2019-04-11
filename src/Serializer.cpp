#include "Serializer.h"
#include "Piece.h"

#include <ctime>
#include <iostream>


Serializer * Serializer::Instance = nullptr;

Serializer::Serializer()
{
}

Serializer::~Serializer()
{
	delete this->Instance;
}

void Serializer::RecordFrame(Game& game)
{
	// Collect Inputs
	int currentPiece = game.GetCurrentPiece().getType();
	int heldPiece = game.GetCurrentPiece().getType();

	std::vector<int> queuedPieces = std::vector<int>();
	std::queue<Piece> queuedPiecesQueue = game.GetQueuedPieces();
	while (!queuedPiecesQueue.empty())
	{
		Piece p = queuedPiecesQueue.front();
		queuedPiecesQueue.pop();
		queuedPieces.push_back(p.getType());
	}

	std::vector<int> gameBoard = std::vector<int>();
	const Matrix& boardMatrix = game.GetGameBoard();
	for (int i = 0; i < boardMatrix.HEIGHT; ++i)
	{
		for (int j = 0; j < boardMatrix.WIDTH; ++j)
		{
			gameBoard.push_back(boardMatrix.get(i, j));
		}
	}

	// Collect Expected Outputs
	int frame = game.GetCurrentPiece().getFrameIndex();
	int column = game.GetCurrentPiece().getColumn();
	int row = game.GetCurrentPiece().getRow();

	std::string sep = "";
	std::ostringstream queuedPieceString;
	for (size_t i = 0; i < queuedPieces.size(); ++i)
	{
		queuedPieceString << sep << queuedPieces[i]; 
		sep = ",";
	}

	sep = "";
	std::ostringstream gameBoardString;
	for (size_t i = 0; i < gameBoard.size(); ++i)
	{
		gameBoardString << sep << gameBoard[i];
		sep = ",";
	}

	std::string formatString =
		"{\"inputs\":{\"currentPiece\":%d,\"heldPiece\":%d,\"queuedPieces\":[%s],\"gameBoard\":[%s]},\"outputs\":{\"frame\":%d,\"row\":%d,\"column\":%d}}";

	char jsonString[4096];
	sprintf(jsonString, formatString.c_str(), currentPiece, heldPiece, queuedPieceString.str().c_str(), gameBoardString.str().c_str(), frame, row, column);

	sep = ",\n";
	if (!file.is_open())
	{
		time_t rawtime;
		struct tm* timeinfo;
		char buffer[80];

		time(&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", timeinfo);

		char fileName[512];
		sprintf(fileName, "../../outputs/%s.json", buffer);

		file.open(fileName);
		file << "[\n";
		sep = "";
	}

	file << sep << jsonString;
	file.flush();
}

void Serializer::Quit()
{
	file << "\n]";
	file.close();
}
