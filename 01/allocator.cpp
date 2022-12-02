#include "allocator.hpp"

void
Allocator::makeAllocator(size_t maxSize)
{
    if (maxSize == 0){
        return;
    }
    offset = 0;
    mx_size = maxSize;
    pointer = new char[maxSize]; 
}

char*
Allocator::alloc(size_t size)
{
    if (size == 0){
        return nullptr;
    }

    if (offset + size > mx_size){
        return nullptr;
    }
    
    char* mem = pointer + offset;

    offset += size;

    return mem;
}

void
Allocator::reset() 
{
    offset = 0;
}

Allocator::~Allocator()     //
{
    delete[] pointer;    
}
