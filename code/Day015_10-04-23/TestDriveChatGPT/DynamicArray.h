#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#pragma once


#include <iostream>

class DynamicArray {
private:
    int* array; // pointer to the dynamically allocated array
    int size; // size of the array
public:
    // constructor that initializes the size of the array and allocates memory using new
    DynamicArray(int n) {
        size = n;
        array = new int[size];
    }
    // copy constructor that creates a deep copy of another DynamicArray object
    DynamicArray(const DynamicArray& other) {
        size = other.size;
        array = new int[size];
        for (int i = 0; i < size; i++) {
            array[i] = other.array[i];
        }
    }
    // destructor that deallocates the memory allocated by the constructor using delete[]
    ~DynamicArray() {
        delete[] array;
    }
    // prints the size of the array and its contents
    void print_array() {
        std::cout << "Array size: " << size << std::endl;
        std::cout << "Array contents: ";
        for (int i = 0; i < size; i++) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
    // fills the array with consecutive integers starting from the specified value
    void fill_array(int start) {
        for (int i = 0; i < size; i++) {
            array[i] = start + i;
        }
    }
};


#endif