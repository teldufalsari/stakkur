#ifndef STACKHDR
#define STACKHDR
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "stack_err.h"

const unsigned long MaximalStCap = ULONG_MAX;
const unsigned long DefaultStCap = 256;

template <typename ElemT>
class Stack
{
private:
    int canary1_;

    size_t size_;
    ElemT *data_;
    int hash1, hash2;
    size_t capacity_;
    void *sample_;
    int (Stack::*Hashes_[7]) ();
    int (Stack<ElemT>::*NewHash1) ();
    int (Stack<ElemT>::*NewHash2) ();

    int canary2_;

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

    char Resize(size_t extension);

    char Push (ElemT value);

    char Pop ();

    char Top (ElemT *target);

    size_t Size();

    char Check();
};

template <typename ElemT>
class StCanSample
{
private:

    int canary_1_;
    int canary_2_;
    void Reset();
    StCanSample();

    friend Stack <ElemT>;

public:
    ~StCanSample() = delete;
};

#include "stack.cpp"
#endif