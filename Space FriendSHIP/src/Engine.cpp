#include "Engine.h"


struct coordinates returnCoordinatesByAngle(float angle)
{
    coordinates direction;
    direction.y = sin(angle * PI / 180);
    direction.x = cos(angle * PI / 180);
    return direction;
}

float returnAngleByCoordinates(coordinates direction)
{

    return atan2(direction.x, -1*direction.y) * 180 / PI;
}

coordinates findCenter(SDL_Rect rct, float angle, coordinates* rotation_center) {
    coordinates c,d;
    c.x = rct.x + rct.w/2;
    c.y = rct.y + rct.h/2;

    if (rotation_center != NULL) {
         d = returnCoordinatesByAngle(angle);
         c.x += d.x;
         c.y += d.y;
    }
    return c;

}
