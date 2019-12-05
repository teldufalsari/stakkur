//
// Created by Yngeborga on 05.12.2019.
//

#include "Container.h"

int Container::GetK1()

{
    return *key1;
}

int Container::GetK2()
{
    return *key2;
}

Container::Container()
{
    key1 = new int;
    key2 = new int;

    *key1 = rand();
    *key2 = rand();
}

Container::~Container()
{
    delete key1;
    delete key2;
}

void Container::ResetKeys()
{
    *key2 = rand();
    *key1 = rand();
}
