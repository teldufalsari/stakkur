#include "stack.h"

template <typename ElemT>
StCanSample<ElemT> Samples;

template<typename ElemT>
Stack<ElemT>::Stack()
{
    srand(time(CLOCK_REALTIME));

    size_ = 0;
    capacity_ = DefaultStCap;

    data_ = (ElemT*) calloc(capacity_, sizeof(ElemT));
    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));

    auto *sample_t = (StCanSample<ElemT>*) calloc(1, sizeof(StCanSample<ElemT>));
    sample_t->Reset();
    sample_ =  sample_t;

    canary1_ = sample_t->canary_1_;
    canary2_ = sample_t->canary_2_;

    InitHashes();
    NewHash2 = NewHash1 = nullptr;

    SetHash();
    hash1 = (this->*NewHash1)();
    hash2 = (this->*NewHash2)();

}

template <typename ElemT>
Stack<ElemT>::Stack(size_t Capacity)
{
    capacity_ = Capacity;
    size_ = 0;

    data_ = (ElemT*) calloc(capacity_, sizeof(ElemT));
    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));

    sample_ = (void*) new StCanSample<ElemT>[1];
    auto *sample_t = (StCanSample<ElemT>*) sample_;

    canary1_ = sample_t->canary_1_;
    canary2_ = sample_t->canary_2_;

    InitHashes();
    NewHash2 = NewHash1 = nullptr;

    SetHash();
    hash1 = (this->*NewHash1)();
    hash2 = (this->*NewHash2)();
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


    sample_ = (void*) new StCanSample<ElemT>[1];
    auto *sample_t = (StCanSample<ElemT>*) sample_;

    canary1_ = sample_t->canary_1_;
    canary2_ = sample_t->canary_2_;

    Hashes_ = (int (**) () ) calloc(7, sizeof(void**));
    if (Hashes_ == nullptr)
        assert(ok(ST_NULLPTR));

    InitHashes();
    NewHash2 = NewHash1 = nullptr;

    SetHash();
    hash1 = (this->*NewHash1)();
    hash2 = (this->*NewHash2)();
}

template<typename ElemT>
Stack<ElemT>::~Stack()
{
    free(data_);
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
    hash1 =  hash2 = 0;
    NewHash2 = NewHash2 = nullptr;
    canary1_ = canary2_ = 0;
}

template<typename ElemT>
char Stack<ElemT>::Resize(size_t extension)
{
    if ((capacity_ + extension) > MaximalStCap)
        return ST_FULL;

    capacity_ += extension;
    realloc(data_, sizeof(ElemT) * capacity_);

    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));

    SetHash();

    hash1 = (this->*NewHash1)();
    hash2 = (this->*NewHash2)();

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
    auto *sample_t = (StCanSample<ElemT>*) sample_;

    if (hash1 != (this->*NewHash1) () )
        return ST_CORRUPTION;

    if (hash2 != (this->*NewHash2) () )
        return ST_CORRUPTION;

    if (canary1_ != sample_t->canary_1_)
        return ST_CORRUPTION;

    if(canary2_ != sample_t->canary_2_)
        return ST_CORRUPTION;

    return SUCCESS;
}

template<typename ElemT>
void Stack<ElemT>::SetHash()
{
    NewHash1 =  *(Hashes_ + (rand() % 7));

    do {
        NewHash2 = *(Hashes_ + (rand() % 7));
    } while (NewHash2 == NewHash1);

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

template<typename ElemT>
StCanSample<ElemT>::StCanSample()
{
    srand(time(CLOCK_REALTIME));
    canary_1_ = rand();
    canary_2_ = rand();
}

template<typename ElemT>
void StCanSample<ElemT>::Reset()
{
    canary_1_ = rand();
    canary_2_ = rand();
}

template <typename ElemT>
void Stack<ElemT>::Reset()
{
    auto *sample_t = (StCanSample<ElemT>*) sample_;

    SetHash();

    hash1 = (this->*NewHash1)();
    hash2 = (this->*NewHash2)();

    sample_t->Reset();

    canary1_ = sample_t->canary_1_;
    canary2_ = sample_t->canary_2_;
}
