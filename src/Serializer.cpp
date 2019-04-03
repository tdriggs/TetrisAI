#include "Serializer.h"

Serializer * Serializer::Instance = nullptr;

Serializer::Serializer()
{
}

Serializer::~Serializer()
{
	delete this->Instance;
}
