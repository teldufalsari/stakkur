#ifndef STACKHDR
#define STACKHDR
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "stack_err.h"
#include "Container.h"

const unsigned long MaximalStCap = ULONG_MAX;
const unsigned long DefaultStCap = 256;

template <typename ElemT>
class Stack
{
private:
    int canary1_;

    size_t size_;
    ElemT *data_;
    int hash1_, hash2_;
    size_t capacity_;

    Container cage_;

    int (Stack::*Hashes_[7]) ();
    int (Stack<ElemT>::*NewHash1_) ();
    int (Stack<ElemT>::*NewHash2_) ();

    int GetHash1();
    int GetHash2();
    int GetHash3();
    int GetHash4();
    int GetHash5();
    int GetHash6();
    int GetHash7();

    void SetHash();
    void InitHashes();
    void Reset();

    int canary2_;

public:

    Stack ();

    explicit Stack(size_t Capacity);

    Stack(const Stack&);

    ~Stack();

    char Resize(size_t extension);

    char Push (ElemT value);

    char Pop ();

    char Top (ElemT *target);

    size_t Size();

    char Check();
};


#include "stack.cpp"
#endif