#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <cmath>
#include <windows.h>
#include <winuser.h>

#define PI 3.14
#define SPEED_FACTOR 1.7

using namespace std;

struct coordinates
{
    float x;
    float y;
};

struct coordinates returnCoordinatesByAngle(float angle);
float returnAngleByCoordinates(struct coordinates direction);

#endif // ENGINE_H
