#ifndef STACKHDR
#define STACKHDR
#include <ctime>
#include <cstring>
#include <cstdlib>
#include "stack_err.h"

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

    int GetHash1();

    int GetHash2();

    void CanaryInit();

public:

    Stack ();

    explicit Stack(size_t Capacity);

    Stack(const Stack&);

    ~Stack();

    void Resize(size_t NewSize);

    char Push (ElemT value);

    char Pop ();

    char Top (ElemT *target);

    size_t Size();

    char Check();
};

#include "stack.cpp"
#endif