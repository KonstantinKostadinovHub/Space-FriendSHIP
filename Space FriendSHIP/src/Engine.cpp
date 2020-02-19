#include "Engine.h"


struct coordinates returnCoordinatesByAngle(struct coordinates direction, float angle)
{
    direction.x += sin(angle) * PI / 180;
    direction.y += cos(angle) * PI / 180;
    return direction;
}

float returnAngleByCoordinates(struct coordinates coor1, struct coordinates direction)
{
    float tanges = direction.y / direction.x;
    float result = 0;
    if (direction.y < 0 && abs(direction.y) > abs(direction.x))
    {
        tanges =  direction.x / direction.y;
        tanges = abs(tanges);
        result = tan(tanges) * 180 / PI;
    }
    else if ( direction.y > 0 && abs(direction.y) > abs(direction.x))
    {
        tanges = direction.x / direction.y;
        tanges = abs(tanges);
        result = 180 - tan(tanges) * 180 / PI;
    }
    else if ( abs(direction.y) < abs(direction.x))
    {
        tanges = direction.y / direction.x;
        tanges = abs(tanges);
        if(direction.y > 0)
        {
            result = tan(tanges) * 180 /PI + 90;
        }
        else
        {
            result = 90 - tan(tanges) * 180 / PI;
        }
    }
    if (direction.x < 0)
    {
        result *= -1;
    }
    return result;
}
