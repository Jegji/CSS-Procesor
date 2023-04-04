#pragma once
#define BLOCKSIZE 8
#include "Section.h"

class Block
{
public:
	Block* next;
	Block* prev;
	Section* tab[BLOCKSIZE];
	int ocupied;

	Block(Block* prev);
	~Block();
	int firstFree();
	void remove(int id);
	void addSection();
};

