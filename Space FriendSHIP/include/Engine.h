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
coordinates findCenter(SDL_Rect rct, float angle, coordinates* rotation_center = NULL);
coordinates findCenter(SDL_Rect rct, float angle, SDL_Point* rotation_center = NULL);
void SaveInFile(string file, string tmp, float value);
float LoadFromFile(string file);
SDL_Texture* LoadTexture(string file, SDL_Renderer* renderer);
bool checkForMouseCollision(int mouseX, int mouseY, SDL_Rect object);
bool checkForCollisionBetweenObjects(SDL_Rect rect_no_rotation1, float angle1, SDL_Point* center1,
                                     SDL_Rect rect_no_rotation2, float angle2, SDL_Point* center2);
bool checkIfOffBounds(SDL_Rect rect, int SCREEN_WIDTH, int SCREEN_HEIGHT);
UIElement* LoadUIElement(string file);
#endif // ENGINE_H
