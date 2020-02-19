#ifndef DUOSHOOTER_H
#define DUOSHOOTER_H

#include "Enemy.h"

class DuoShooter : public Enemy
{
    public:
        DuoShooter();
        virtual ~DuoShooter();

        virtual void init(string configFile, coordinates coor, coordinates direction);
    protected:

    private:
};

#endif // DUOSHOOTER_H
