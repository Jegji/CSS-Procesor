#include "String.h"

String::String() : txt(nullptr), lng(0) {
    txt = nullptr;
}

String::String(char* data, int lng){
    this->lng = lng;
    txt = new char[lng+1];
    memcpy(txt, data, lng);
    txt[lng] = '\n';
}

String::String(const char* data) {
    lng = std::strlen(data);
    txt = new char[lng + 1];
    strcpy(txt, data);
}

String::String(const String& other): lng(other.lng) {
    txt = new char[lng + 1];
    std::strcpy(txt, other.txt);
}

String::~String(){
   // delete[] txt;
}

size_t String::length() const
{
    return lng;
}

const char* String::str() const
{
    return txt;
}

bool String::operator==(const String& other) const
{
    return strcmp(txt, other.txt) == 0;
}

void String::print()
{
    for (int i = 0; i < lng; i++)
        std::cout << txt[i];
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
    for(int i=0;i<str.lng;i++)
    os << str.txt[i];
    return os;
}