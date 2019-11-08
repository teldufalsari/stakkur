template<typename ElemT>
Stack<ElemT>::Stack()
{
    size_ = 0;
    data_ = nullptr;
    capacity_ = 0;
    hash1 = hash2 = 0;
}

template <typename ElemT>
Stack<ElemT>::Stack(size_t Capacity)
{
    capacity_ = Capacity;
    size_ = 0;
    data_ = (ElemT*) calloc(capacity_, sizeof(ElemT));

    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));
}

template <typename ElemT>
Stack<ElemT>::Stack(const Stack& Origin)
{
    size_ = Origin.size_;
    capacity_ = Origin.capacity_;

    data_ = (ElemT*) calloc(capacity_, sizeof(ElemT));
    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));

    void* state = memcpy(data_, Origin.data_, sizeof(ElemT) * capacity_);
    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));
}

template<typename ElemT>
Stack<ElemT>::~Stack()
{
    free(data_);
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

template<typename ElemT>
void Stack<ElemT>::Resize(size_t NewSize)
{
    capacity_ += NewSize;
    realloc(data_, sizeof(ElemT) * capacity_);

    if (data_ == nullptr)
        assert(ok(ST_NULLPTR));
}

template<typename ElemT>
char Stack<ElemT>::Push(ElemT value) {
    if (size_ >= capacity_)
        return ST_FULL;

    data_[size_++] = value;
    return SUCCESS;
}

template<typename ElemT>
char Stack<ElemT>::Pop()
{
    if (size_ == 0)
        return ST_EMPTY;

    size_--;
    return SUCCESS;
}

template<typename ElemT>
char Stack<ElemT>::Top(ElemT *target) {
    if (size_ == 0)
        return ST_EMPTY;

    *target = data_[size_ - 1];
    return SUCCESS;
}

template<typename ElemT>
size_t Stack<ElemT>::Size()
{
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
void Stack<ElemT>::CanaryInit()
{
   
}

template <typename ElemT>
char Stack<ElemT>::Check()
{
    if (hash1 != GetHash1())
        return ST_CORRUPTION;

    if (hash2 != GetHash2())
        return ST_CORRUPTION;


    return SUCCESS;
}