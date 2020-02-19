#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <cmath>
#include <windows.h>
#include <winuser.h>

#define PI 3.14

using namespace std;

struct coordinates
{
    float x;
    float y;
};

struct coordinates returnCoordinatesByAngle(struct coordinates direction, float angle);
float returnAngleByCoordinates(struct coordinates coor1, struct coordinates coor2);

#endif // ENGINE_H
