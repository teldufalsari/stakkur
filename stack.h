#ifndef STACKHDR
#define STACKHDR
#include "stack_err.h"
#include <cstring>

template <typename ElemT>
class Stack
{
private:
    int canary1;
    size_t size_;
    ElemT *data_;
    int hash1, hash2;
    size_t capacity_;
    int canary2;

public: Stack ();
    explicit Stack(size_t Capacity);

    Stack(const Stack&);

    ~Stack();

    char Push (ElemT value);

    char Pop ();

    char Top (ElemT *target);

    size_t Size();
};

#include "stack.cpp"
#endif