#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

//inspired by https://www.geeksforgeeks.org/how-to-create-a-custom-string-class-in-c-with-basic-functionalities/
class String {
    char* str;

public:
    String();

    String(char* val);

    String(const String& source);

    ~String() {
        delete[] str;
    }

    friend ostream& operator<<(ostream& os, const String& string);

    friend String operator+(const String& a, const String& b);
    friend bool operator<(const String& a, const String& b);
    friend bool operator<=(const String& a, const String& b);
    friend bool operator>(const String& a, const String& b);
    friend bool operator==(const String& a, const String& b);
    friend bool operator!=(const String& a, const String& b);

    bool is_subStr(String subStr);

    bool isEmpty() const;

    void push_back(char a);

    void pop_back();

    int size();

    String& operator=(const String& string);
    String& operator=(const char* string);
};

String::String(){
    str = new char[1];
    str[0] = '\0';
}

String::String(char* val){
    if (val == nullptr) {
        str = new char[1];
        str[0] = '\0';
    }
    else {
        str = new char[strlen(val) + 1];
        strcpy(str, val);
        str[strlen(val)] = '\0';
    }
}

String::String(const String& source){
    str = new char[strlen(source.str) + 1];
    strcpy(str, source.str);
    str[strlen(source.str)] = '\0';
}

String& String::operator=(const String& string){
    if (this == &string)
        return *this;
    delete[] str;
    str = new char[strlen(string.str) + 1];
    strcpy(str, string.str);
    return *this;
}

String& String::operator=(const char* string){
    if (this->str == string)
        return *this;
    delete[] str;
    str = new char[strlen(string) + 1];
    strcpy(str, string);
    return *this;
}

String operator+(const String& a, const String& b){
    int length = strlen(a.str) + strlen(b.str);

    char* buff = new char[length + 1];

    strcpy(buff, a.str);
    strcat(buff, b.str);
    buff[length] = '\0';

    String tmp(buff) ;

    delete[] buff;

    return tmp;
}

ostream& operator<<(ostream& os, const String& string){
    os << string.str;

    return os;
}

void String::push_back(char a){
    int length = strlen(str);

    char* buff = new char[length + 2];

    for (int i = 0; i < length; i++) {
        buff[i] = str[i];
    }
    buff[length] = a;
    buff[length + 1] = '\0';

    *this = String(buff);

    delete[] buff;
}

int String::size(){
    return strlen(str);
}

bool operator<(const String& a, const String& b){
    return ::strcmp(a.str, b.str) < 0;
}

bool operator<=(const String& a, const String& b){
    return ::strcmp(a.str, b.str) <= 0;
}

bool operator==(const String& a, const String& b){
    return ::strcmp(a.str, b.str) == 0;
}

bool operator>(const String& a, const String& b){
    return ::strcmp(a.str, b.str) > 0;
}

bool operator!=(const String& a, const String& b){
    return ::strcmp(a.str, b.str) != 0;
}

bool String::isEmpty() const{
    return ::strlen(str) == 0;
}

void String::pop_back() {
    int length = strlen(str);
    char* buff = new char[length];

    for (int i = 0; i < length - 1; i++)
        buff[i] = str[i];
    buff[length-1] = '\0';

    *this = String{ buff };

    delete[] buff;
}

bool String::is_subStr(String subStr) {
    char * res = strstr(str, subStr.str);
    if (res != nullptr){
        return true;
    }
    return false;
}
