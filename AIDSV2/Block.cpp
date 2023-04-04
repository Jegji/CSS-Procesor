#include "Block.h"

Block::Block(Block* prev)
{
	this->prev = prev;
	this->next = nullptr;
	ocupied = 0;
	for (int i = 0; i < BLOCKSIZE; i++)
		tab[i] = nullptr;
}

Block::~Block()
{
	for (int i = 0; i < ocupied; i++) {
		tab[i]->~Section();
	}delete[] tab;
}

int Block::firstFree()
{
	for (int i = 0; i < BLOCKSIZE; i++)
		if (tab[i] == nullptr)
			return i;
	return -1;
}

void Block::remove(int id)
{
	ocupied--;
	tab[id]->~Section();
	while (id != BLOCKSIZE) {
		tab[id] = tab[id + 1];
		id++;
	}
	tab[BLOCKSIZE-1] = nullptr;
}

void Block::addSection()
{
	if (tab[BLOCKSIZE - 1] == nullptr) {
		tab[firstFree()] = new Section();
		ocupied++;
	}
	else {
		next = new Block(this);
		next->addSection();
	}
}
