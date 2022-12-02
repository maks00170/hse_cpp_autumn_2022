#pragma once

#include <iostream>

class Allocator
{
public:
    void makeAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    // Это деструктор!
    ~Allocator();
private:
    size_t mx_size; // размер памяти
    size_t offset; // смещение указателя памяти
    char * pointer; // указатель на выделяемую память
};