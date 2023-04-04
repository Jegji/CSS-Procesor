#pragma once
#include "Block.h"
class BlockList
{
	Block* head;
	Block* tail;
	size_t size;
public:
	int ocupied();
	void remove(int id);
	BlockList();
	~BlockList();
	void addSection();
	Section* last();
	Section* getbyid(int id);
};

