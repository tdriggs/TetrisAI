#pragma once

#include "rapidjson.h"

#include "Game.h"
#include <sstream>
#include <fstream>

#define SERIALIZER Serializer::GetInstance()

class Serializer
{
private:
	static Serializer * Instance;

	std::ofstream file;

	// ***** Singleton *****
public:
	Serializer();

	~Serializer();

	static Serializer * GetInstance()
	{
		if (Serializer::Instance == NULL)
		{
			Serializer::Instance = new Serializer();
		}
		return Serializer::Instance;
	}

	// ***** Util Functions *****
public:
	void RecordFrame(const Game& game);

	void Quit();
};
