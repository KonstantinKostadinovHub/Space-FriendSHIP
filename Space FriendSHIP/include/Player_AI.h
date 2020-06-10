#ifndef PLAYER_AI_H
#define PLAYER_AI_H

#include <chrono>

#include "Player.h"
#include "SoundManager.h"

class Player_AI : public Player
{
public:
    Player_AI();
    virtual ~Player_AI();

    SDL_Rect m_desiredPos;

    const int MIN_DIST = 135;

    int m_clockwise;
    int m_indexOfEngagement;

    bool m_follow;

    chrono::high_resolution_clock::time_point m_elapsed_engage;
    chrono::duration<float> m_engagementRate;

    virtual void init(string config, SDL_Renderer* renderer);
    virtual void update();
    virtual void draw(SDL_Renderer* renderer);

private:
    void engage();
    void moveToTarget();
    void shoot();
};

#endif
