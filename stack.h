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
    size_t size_;
    ElemT *data_;
    int hash1, hash2;
    size_t capacity_;



    int  (Stack::*Hashes_[7]) ();

    int (Stack<ElemT>::*NewHash1) ();
    int (Stack<ElemT>::*NewHash2) ();

    int GetHash1();
    int GetHash2();
    int GetHash3();
    int GetHash4();
    int GetHash5();
    int GetHash6();
    int GetHash7();

    void SetHash();
    void InitHashes();

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