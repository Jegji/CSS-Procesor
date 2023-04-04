#include "Section.h"

Section::Section()
{
	selectors = new List<String>;
	atributs = new List<Atribute>;
}

Section::~Section()
{
	delete selectors;
	delete atributs;
}
