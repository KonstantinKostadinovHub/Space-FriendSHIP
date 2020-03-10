#ifndef ZIGZAG_H
#define ZIGZAG_H

#include "Shooter.h"

class ZigZag : public Shooter
{
    public:
        ZigZag();
        virtual ~ZigZag();

        float m_rotatedUntilNow;
        float m_startRotation;
        float m_maxRotation;
        float m_rotationFactor;
        bool m_rotateRight;

        virtual void init(string configFile, coordinates coor, float rotation, SDL_Renderer* renderer);
        virtual void update();
        virtual void draw(SDL_Renderer* renderer);
    protected:

    private:
};

#endif // ZIGZAG_H
