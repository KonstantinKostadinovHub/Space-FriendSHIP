#ifndef CANNON_H
#define CANNON_H

#include "Enemy.h"

class Cannon : public Enemy
{
    public:
        Cannon();
        virtual ~Cannon();

        struct coordinates m_playerCoor;

        virtual void getPlayerCoor(coordinates playerCoor);
        virtual void update();
        virtual void init(string configFile, coordinates coor, coordinates direction);
    protected:

    private:
};

#endif // CANNON_H
