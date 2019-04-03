#pragma once

#include "rapidjson.h"

#define SERIALIZER Serializer::GetInstance()

class Serializer
{
private:
	static Serializer * Instance;

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
	
};
