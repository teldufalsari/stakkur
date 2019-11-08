template<typename ElemT>
Stack<ElemT>::Stack()
{
    size_ = 0;
    data_ = nullptr;
    capacity_ = 0;
}

template <typename ElemT>
Stack<ElemT>::Stack(size_t Capacity)
{
    capacity_ = Capacity;
    data_ = (ElemT*) calloc(capacity_, sizeof(ElemT));
    size_ = 0;
}

template <typename ElemT>
Stack<ElemT>::Stack(const Stack& Origin)
{
    size_ = Origin.size_;
    capacity_ = Origin.capacity_;
    data_ = (ElemT*) calloc(capacity_, sizeof(ElemT));
    memcpy(data_, Origin.data_, sizeof(ElemT) * capacity_);
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