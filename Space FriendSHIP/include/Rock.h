#ifndef ROCK_H
#define ROCK_H

#include "Enemy.h"

class Rock : public Enemy
{
public:
    Rock();
    virtual ~Rock();

    virtual void update();
protected:

private:
};

#endif // ROCK_H
