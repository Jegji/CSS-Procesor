#include "BlockList.h"

int BlockList::ocupied()
{
	int sum = 0;
	Block* temp = head;
	if (temp != nullptr) {
		for (int i = 0; i < size; i++) {
			sum += temp->ocupied;
			temp = temp->next;
		}return sum;
	}
	return sum;
}

void BlockList::remove(int id)
{
	int sum = 0;
	Block* temp;
	temp = head;
	for (int i = 0; i < size; i++) {
		if (sum + temp->ocupied > id) {
			temp->remove(id - sum);
			return;
		}sum += temp->ocupied;
		temp = temp->next;
	}return;
}

BlockList::BlockList()
{
	head = new Block(nullptr);
	head->addSection();
	tail = head;
	size = 1;
}

BlockList::~BlockList()
{
	Block* temp = head;
	while (temp != nullptr) {
		temp = temp->next;
		temp->prev->~Block();
		delete temp->prev;
	}delete temp;
}

void BlockList::addSection()
{
	tail->addSection();
	if (tail->next != nullptr) {
		tail = tail->next;
		size++;
	}
}

Section* BlockList::last()
{
	return tail->tab[tail->ocupied-1];
}

Section* BlockList::getbyid(int id)
{
	int sum = 0;
	Block* temp;
	temp = head;
	for (int i = 0; i < size; i++) {
		if (sum + temp->ocupied > id) {
			return temp->tab[id - sum];
		}sum += temp->ocupied;
		temp = temp->next;
	}return nullptr;
}
