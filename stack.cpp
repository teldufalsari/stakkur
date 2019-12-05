#include "stack.h"

template<typename ElemT>
Stack<ElemT>::Stack()
{
    srand(time(CLOCK_REALTIME));

    size_ = 0;
    capacity_ = DefaultStCap;

    data_ = (ElemT*) calloc(capacity_, sizeof(ElemT));
    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));

    InitHashes();
    NewHash2_ = NewHash1_ = nullptr;

    SetHash();
    hash1_ = (this->*NewHash1_)();
    hash2_ = (this->*NewHash2_)();

    canary1_ = cage_.GetK1();
    canary2_ = cage_.GetK2();

}

template <typename ElemT>
Stack<ElemT>::Stack(size_t Capacity)
{
    capacity_ = Capacity;
    size_ = 0;

    data_ = (ElemT*) calloc(capacity_, sizeof(ElemT));
    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));

    InitHashes();
    NewHash2_ = NewHash1_ = nullptr;

    SetHash();
    hash1_ = (this->*NewHash1_)();
    hash2_ = (this->*NewHash2_)();

    canary1_ = cage_.GetK1();
    canary2_ = cage_.GetK2();
}

template <typename ElemT>
Stack<ElemT>::Stack(const Stack& Origin)
{
    size_ = Origin.size_;
    capacity_ = Origin.capacity_;

    data_ = (ElemT*) calloc(capacity_, sizeof(ElemT));
    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));

    memcpy(data_, Origin.data_, sizeof(ElemT) * capacity_);
    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));
    
    Hashes_ = (int (**) () ) calloc(7, sizeof(void**));
    if (Hashes_ == nullptr)
        assert(ok(ST_NULLPTR));

    InitHashes();
    NewHash2_ = NewHash1_ = nullptr;

    SetHash();
    hash1_ = (this->*NewHash1_)();
    hash2_ = (this->*NewHash2_)();

    canary1_ = cage_.GetK1();
    canary2_ = cage_.GetK2();
}

template<typename ElemT>
Stack<ElemT>::~Stack()
{
    free(data_);
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    hash1_ = hash2_ = 0;
    NewHash2_ = NewHash2_ = nullptr;
    canary1_ = canary2_ = 0;
}

template<typename ElemT>
char Stack<ElemT>::Resize(size_t extension)
{
    assert(ok(Check()));

    if ((capacity_ + extension) > MaximalStCap)
        return ST_FULL;

    capacity_ += extension;
    realloc(data_, sizeof(ElemT) * capacity_);

    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));

    this->Reset();

    return SUCCESS;
}

template<typename ElemT>
char Stack<ElemT>::Push(ElemT value)
{
    assert(ok(Check()));

    if (size_ >= capacity_)
        if(Resize(DefaultStCap) == ST_FULL)
            return ST_FULL;


    data_[size_++] = value;

    this->Reset();

    return SUCCESS;
}

template<typename ElemT>
char Stack<ElemT>::Pop()
{
    assert(ok(Check()));

    if (size_ == 0)
        return ST_EMPTY;

    size_--;

    this->Reset();

    return SUCCESS;
}

template<typename ElemT>
char Stack<ElemT>::Top(ElemT *target)
{
    assert(ok(Check()));

    if (size_ == 0)
        return ST_EMPTY;

    *target = data_[size_ - 1];

    this->Reset();

    return SUCCESS;
}

template<typename ElemT>
size_t Stack<ElemT>::Size()
{
    assert(ok(Check()));
    return size_;
}

template<typename ElemT>
int Stack<ElemT>::GetHash1()
{
    int hash = 0;

    for (size_t i = 0; i < capacity_; i++)
    {
        hash += data_[i];
    }

    return hash % 167;
}

template<typename ElemT>
int Stack<ElemT>::GetHash2()
{
    int hash = 1;

    for (size_t i = 0; i < capacity_; i++)
    {
        hash *= 1 + data_[i];
    }

    return hash % 107;
}

template<typename ElemT>
int Stack<ElemT>::GetHash3()
{
    int hash = 0;

    for (size_t i = 0; i < capacity_; i++)
    {
        hash += data_[i];
    }

    return hash % 101;
}

template<typename ElemT>
int Stack<ElemT>::GetHash4()
{
    int hash = 0;

    for (size_t i = 0; i < capacity_; i++)
    {
        hash += data_[i];
        hash %= 97;
    }

    return hash;
}

template<typename ElemT>
int Stack<ElemT>::GetHash5()
{
    int hash = 0;

    for (size_t i = 0; i < capacity_; i++)
    {
        hash += data_[i];
        hash %= 29;
    }

    return hash;
}

template<typename ElemT>
int Stack<ElemT>::GetHash6()
{
    int hash = 1;

    for (size_t i = 0; i < capacity_; i++)
    {
        hash *= -1 + data_[i];
    }

    return hash % 113;
}

template<typename ElemT>
int Stack<ElemT>::GetHash7()
{
    int hash = 1;

    for (size_t i = 0; i < capacity_; i++)
    {
        hash *= 2 + data_[i];
    }

    return hash % 71;
}

template <typename ElemT>
char Stack<ElemT>::Check()
{
    if (hash1_ != (this->*NewHash1_) () )
        return ST_CORRUPTION;

    if (hash2_ != (this->*NewHash2_) () )
        return ST_CORRUPTION;

    if (canary1_ != cage_.GetK1())
        return ST_CORRUPTION;

    if (canary2_ != cage_.GetK2())
        return ST_CORRUPTION;

    return SUCCESS;
}

template<typename ElemT>
void Stack<ElemT>::SetHash()
{
    NewHash1_ =  *(Hashes_ + (rand() % 7));

    do {
        NewHash2_ = *(Hashes_ + (rand() % 7));
    } while (NewHash2_ == NewHash1_);

}

template<typename ElemT>
void Stack<ElemT>::InitHashes()
{
    Hashes_[0] = &Stack::GetHash1;
    Hashes_[1] = &Stack::GetHash2;
    Hashes_[2] = &Stack::GetHash3;
    Hashes_[3] = &Stack::GetHash4;
    Hashes_[4] = &Stack::GetHash5;
    Hashes_[5] = &Stack::GetHash6;
    Hashes_[6] = &Stack::GetHash7;
}

template <typename ElemT>
void Stack<ElemT>::Reset()
{

    SetHash();

    hash1_ = (this->*NewHash1_)();
    hash2_ = (this->*NewHash2_)();

    cage_.ResetKeys();

    canary1_ = cage_.GetK1();
    canary2_ = cage_.GetK2();

}
