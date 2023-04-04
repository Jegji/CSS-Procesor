#include "BlockList.h"
#include "Atribute.h"
#include "Block.h"
#include "List.h"
#include "Section.h"
#include "String.h"

#include <iostream>

enum ReadingState {
	css,
	command
};

enum CssState {
	atribute,
	selector,
	value
};

void Print(BlockList* Css) {
	for (int i = 0; i < Css->ocupied(); i++) {
		for (int j = 0; j < Css->getbyid(i)->selectors->length(); j++) {
			Css->getbyid(i)->selectors->getbyid(j)->print();
			std::cout << std::endl;
		}
		for (int k = 0; k < Css->getbyid(i)->atributs->length(); k++) {
			std::cout << "\t";
			Css->getbyid(i)->atributs->getbyid(k)->print();
			std::cout<<std::endl;
		}
	}
}

int tonumber(char* txt, int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum = sum * 10;
		sum += txt[i] - '0';
	}return sum;
}
int findAtribute(List<Atribute>* list,char* txt,int lng) {
	for (int i = 0; i < list->length(); i++) {
		const char* txt2 = list->getbyid(i)->name.str();
		int temp = strncmp(txt, list->getbyid(i)->name.str(), lng-1);
		if (temp==0) {
			return i;
		}
	}return -1;
}
int findSelector(List<String>* list, char* txt) {
	for (int i = 0; i < list->length(); i++) {
		const char* txt2 = list->getbyid(i)->str();
		int temp = strncmp(txt, list->getbyid(i)->str(), list->getbyid(i)->lng);
		if (temp == 0) {
			return i;
		}
	}return -1;
}

void Acommand(BlockList* Css, char* command, int lng) {
	char* separator = strstr(command, ",A,");
	int size = separator - command;
	char* first_segment = new char[size];
	char* second = new char[lng - size - 3];
	strncpy(first_segment, command, size);
	strncpy(second, separator + 3, lng - size - 3);

	if (*first_segment - '0' < 9 && *first_segment - '0' > -1) {
		int number = tonumber(first_segment, size) - 1;
		if (number > Css->ocupied() - 2)return;
		if (*second == '?') {
			std::cout << command << " == " << Css->getbyid(number)->atributs->length() << std::endl;
			delete[] first_segment, second, separator;
			return;
		}
		else {
			int id = findAtribute(Css->getbyid(number)->atributs, second, lng - size - 3);
			if (id != -1) {
				std::cout << command << " ==" << Css->getbyid(number)->atributs->getbyid(id)->value << std::endl;
				delete[] first_segment, second, separator;
				return;
			}
		}
	}
	else {
		int sum = 0;
		for (int i = 0; i < Css->ocupied() - 1; i++) {
			if (findAtribute(Css->getbyid(i)->atributs, first_segment, lng - size - 3) != -1) {
				sum++;
			}
		}
		std::cout << command << " == " << sum << std::endl;
		delete[] first_segment, second, separator;
		return;
	}


	delete[] first_segment, second, separator;

}
void Scommand(BlockList* Css, char* command, int lng) {
	char* separator = strstr(command, ",S,");
	int size = separator - command;
	char* first_segment = new char[size];
	char* second = new char[lng - size - 4];
	strncpy(first_segment, command, size);
	strncpy(second, separator + 3, lng - size - 4);

	if (*first_segment - '0' < 9 && *first_segment - '0' > -1) {
		int number = tonumber(first_segment, size) - 1;
		if (number > Css->ocupied() - 2)return;
		if (*second == '?') {
			std::cout << command << " == " << Css->getbyid(number)->selectors->length() << std::endl;
			delete[] first_segment, second, separator;
			return;
		}
		else {
			int number2 = tonumber(second, lng - size - 4) - 1;
			if (number2 > Css->getbyid(number)->selectors->length()) {
				return;
			}
			else {
				String* tempStr = Css->getbyid(number)->selectors->getbyid(number2);
				if (tempStr != nullptr) {
					std::cout << command << " == ";
					tempStr->print();
					std::cout << std::endl;
				}
				delete[] first_segment, second, separator;
				return;
			}
		}
	}
	else {
		int sum = 0;
		for (int i = 0; i < Css->ocupied() - 1; i++) {
			if (findSelector(Css->getbyid(i)->selectors, first_segment) != -1) {
				sum++;
			}
		}
		std::cout << command << " == " << sum << std::endl;
	}


	delete[] first_segment, second, separator;

}
void Dcommand(BlockList* Css, char* command, int lng) {
	char* separator = strstr(command, ",D,");
	int size = separator - command;
	char* first_segment = new char[size];
	char* second = new char[lng - size - 4];
	strncpy(first_segment, command, size);
	strncpy(second, separator + 3, lng - size - 4);

	if (*first_segment - '0' < 9 && *first_segment - '0' > -1) {
		int number = tonumber(first_segment, size) - 1;
		if (number > Css->ocupied() - 2)return;
		if (*second == '*') {
			Css->remove(number);
			std::cout << command << " == deleted" << std::endl;
			delete[] first_segment, second, separator;
			return;
		}
		else {
			Css->getbyid(number)->atributs->remove(findAtribute(Css->getbyid(number)->atributs, second, lng - size - 3));
			if (Css->getbyid(number)->atributs->length() == 0)Css->remove(number);
			std::cout << command << " == deleted" << std::endl;
			delete[] first_segment, second, separator;
			return;
		}
	}


	delete[] first_segment, second, separator;

}
void Ecommand(BlockList* Css, char* command, int lng) {
	char* separator = strstr(command, ",E,");
	int size = separator - command;
	char* first_segment = new char[size];
	char* second = new char[lng - size - 4];
	strncpy(first_segment, command, size);
	strncpy(second, separator + 3, lng - size - 4);

	for (int i = Css->ocupied() - 1; i >= 0; i--) {
		int id = findSelector(Css->getbyid(i)->selectors, first_segment);
		if (id != -1) {
			int id2 = findAtribute(Css->getbyid(i)->atributs, second, lng - size - 3);
			if (id2 != -1) {
				std::cout << command << " == ";
				Css->getbyid(i)->atributs->getbyid(id2)->value.print();
				std::cout << std::endl;
				delete[] first_segment, second, separator;
				return;
			}

		}
	}


	delete[] first_segment, second, separator;

}

void readCss(BlockList* Css, ReadingState* rState) {
	char sign;
	static CssState state = selector;
	static char buffor[128];
	static int lng = 0;
	String* temp;

	char peek = std::cin.peek();
	if (peek == '?' && *rState == css) {
		*rState = command;
		std::cin.ignore(5);
		return;
	}

	sign = std::cin.get();

	switch (sign)
	{
	case '{':
		temp = new String(buffor, lng);
		Css->last()->selectors->insertBack(temp);
		lng = 0;
		state = atribute;
		break;
	case '}':
		if (lng >= 3) {
			temp = new String(buffor, lng);
			Css->last()->atributs->insertBack(new Atribute(*temp));
			delete temp;
		}
		lng = 0;
		Css->addSection();
		state = selector;
		break;
	case ',':
		if (state == selector) {
			temp = new String(buffor, lng);
			Css->last()->selectors->insertBack(temp);
			lng = 0;
		}
		else {
			buffor[lng] = sign;
			lng++;
		}
		break;
	case ';':
		temp = new String(buffor, lng);
		Css->last()->atributs->insertBack(new Atribute(*temp));
		//delete temp;
		state = atribute;
		lng = 0;
		break;
	case '\n':

		break;

	case '\t':

		break;
	default:
		if (sign == ' ' && lng == 0) {
			break;
		}
		buffor[lng] = sign;
		lng++;
		break;
	}
}
void readingCommand(BlockList* Css,ReadingState* rState) {
	char buffor[64];
	char* command;
	if (std::cin.peek() == '*') {
		std::cin.ignore(4);
		*rState = css;
	}
	else {
		std::cin.getline(buffor, 64);
		command = new char[std::cin.gcount()];
		int lng = std::cin.gcount();
		if (buffor[lng-2] == ',')return;
		memcpy(command, buffor, lng);
		if (strstr(command, ",A,") != NULL) {
			Acommand(Css,command, lng);
		}
		else if (strstr(command, ",S,") != NULL) {
			Scommand(Css, command, lng);
		}
		else if (strstr(command, ",E,") != NULL) {
			Ecommand(Css, command, lng);
		}
		else if (strstr(command, ",D,") != NULL) {
			Dcommand(Css, command, lng);
		}
		else {
			if(*buffor == '?')
			std::cout <<command<<" == "<< Css->ocupied() - 1 << std::endl;
		}
		delete[] command;
	}
}

int main() {
	BlockList* Css = new BlockList();
	ReadingState rState = css;

	while(!std::cin.eof()) {
		if (rState == css) {
			readCss(Css, &rState);
		}
		else {
			readingCommand(Css, &rState);
		}
	}
}