#pragma once
#include "String.h"
class Atribute
{
public:
	String name;
	String value;
	Atribute(String value);
	void print();
	~Atribute();
};

