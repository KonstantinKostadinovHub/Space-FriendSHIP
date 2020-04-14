#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <cmath>
#include <windows.h>
#include <winuser.h>
#include <fstream>
#include <iostream>

#include <SDL2/SDL.h>

#define PI 3.14
#define SPEED_FACTOR 1.2

using namespace std;

struct coordinates
{
    float x;
    float y;
};

struct UIElement
{
    SDL_Rect* objectRect;
    SDL_Texture* objectTexture;
};

struct coordinates returnCoordinatesByAngle(float angle);
float returnAngleByCoordinates(struct coordinates direction);
coordinates findCenter(SDL_Rect rct, float angle, coordinates* rotation_center);
coordinates findCenter(SDL_Rect rct, float angle, SDL_Point* rotation_center);
void SaveInFile(string file, string tmp, float value);
float LoadFromFile(string file);
SDL_Texture* LoadTexture(string file, SDL_Renderer* renderer);
bool checkForMouseCollision(int mouseX, int mouseY, SDL_Rect object);
UIElement* LoadUIElement(string file);
#endif // ENGINE_H
