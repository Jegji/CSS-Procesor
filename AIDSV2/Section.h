#pragma once
#include "String.h"
#include "List.h"
#include "Atribute.h"
class Section
{
public:
	List<String>* selectors;
	List<Atribute>* atributs;
	Section();
	~Section();
};

