//
// Created by Yngeborga on 05.12.2019.
//

#ifndef STAKKUR_CONTAINER_H
#define STAKKUR_CONTAINER_H


class Container
{
private:
    int* key1;
    int* key2;

public:
    Container();
    ~Container();
    int GetK1();
    int GetK2();
    void ResetKeys();
};

#include "Container.cpp"
#endif //STAKKUR_CONTAINER_H
