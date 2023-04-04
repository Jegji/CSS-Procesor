#include "Atribute.h"

Atribute::Atribute(String value)
{
	const char* pos = strchr(value.str(), 58); // ':' ASCII -> 58
	
	int size = pos - value.str();
	char* temp = new char[size];
	memcpy(temp, value.str(), size);
	name = *new String(temp, size);
	//delete[] temp;

	size = value.length() - size - 1;
	temp = new char[size+1];
	memcpy(temp, pos + 1, size);
	this->value = *new String(temp, size);
	//delete[] temp;
}

void Atribute::print()
{
	name.print();
	std::cout << " - ";
	value.print();
}

Atribute::~Atribute()
{
	name.~String();
	value.~String();
}
