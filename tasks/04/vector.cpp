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

//inspired by https://habr.com/ru/post/593803/
template<typename T>
class Vector {
public:
    Vector() {
        array = new T[1];
        capacity = 1;
        length = 0;
    }

    Vector(int capacity) {
        array = new T[capacity];
        this->capacity = capacity;
        length = 0;
    }

    Vector(const Vector& other) {
        array = new T[other.capacity];
        for (size_t i = 0; i < other.length; i++) array[i] = other.array[i];
        length = other.length;
        capacity = other.capacity;
    }

    ~Vector() {
        delete[] array;
    }

    bool isEmpty() const {
        return length == 0;
    }

    size_t size() const {
        return length;
    }

    void resize() {
        capacity *= 2;
        T* tmp = array;
        array = new T[capacity];
        for (size_t i = 0; i < length; i++) array[i] = tmp[i];
        delete[] tmp;
    }

    void pushBack(const T& value) {
        if (length >= capacity) resize();
        array[length++] = value;
    }

    void erase(size_t index) {
        for (size_t i = index + 1; i < length; i++) {
            array[i - 1] = array[i];
        }
        length -= 1;
    }

    void insert(int index, const T& value){
        if (index <= length) {
            int tmp = 0;
            if (length >= capacity) resize();
            for (size_t i = index; i < length + 1; i++) {
                int temp = 0;
                if (i != length) {
                    temp = array[i];
                }
                array[i] = tmp;
                tmp = temp;
            }
            array[index] = value;

            length += 1;
        }
    }

    T& operator[](size_t index)  {
        return array[index];
    }

    const T& operator[](size_t index) const {
        return array[index];
    }

    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] array;
            array = new T[other.capacity];
            for (size_t i = 0; i < other.length; i++) array[i] = other.array[i];
            length = other.length;
            capacity = other.capacity;
        }
        return *this;
    }
private:
    T* array;
    size_t length{};
    size_t capacity{};
};
