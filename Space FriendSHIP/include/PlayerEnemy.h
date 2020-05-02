#ifndef PLAYERENEMY_H
#define PLAYERENEMY_H

#include "Shooter.h"
#include "Player.h"

class PlayerEnemy: public Shooter
{
public:
    PlayerEnemy();
    virtual ~PlayerEnemy();

    SDL_Rect m_desiredPos;
    const int MIN_DIST = 135;
    int m_clockwise;
    Player* m_target = new Player;

    virtual void load(string config, SDL_Renderer* renderer);
    virtual void init(string config, coordinates coor, float rotation, Enemy* enemy, Player* player);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);
protected:

private:
    void engage();
    void moveToTarget();
    void shoot();
};

#endif // PLAYERENEMY_H
