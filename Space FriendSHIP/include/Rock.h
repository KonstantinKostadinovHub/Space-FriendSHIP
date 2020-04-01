#ifndef ROCK_H
#define ROCK_H

#include "Enemy.h"
#include <fstream>
#include <cstring>

class Rock: public Enemy
{
public:
    Rock();
    virtual ~Rock();
    string tmp;

protected:

private:
};

#endif // ROCK_H
