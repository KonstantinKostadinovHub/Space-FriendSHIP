#ifndef ROCK_H
#define ROCK_H

#include <fstream>
#include <cstring>

#include "Enemy.h"

class Rock: public Enemy
{
public:
    Rock();
    virtual ~Rock();
};

#endif
