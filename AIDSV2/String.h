#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <string.h>
#include <iostream>
class String {
private:
    char* txt;
public:
    size_t lng;
    String();
    String(char* data, int lng);
    String(const char* data);
    String(const String& other);

    ~String();

    size_t length() const;
    const char* str() const;
    bool operator==(const String& other) const;
    void print();

    friend std::ostream& operator<<(std::ostream& os, const String& str);
};