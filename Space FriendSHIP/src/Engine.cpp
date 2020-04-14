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

coordinates findTip(SDL_Rect rct, float angle, coordinates* rotation_center)
{
    coordinates c,d;
    c.x = rct.x + rct.w/2;
    c.y = rct.y + rct.h/2;

    if (rotation_center == NULL)
    {
        d = returnCoordinatesByAngle(angle);
        c.x += d.x;
        c.y += d.y;
    }
    return c;

}

coordinates rotatePointByAngle(coordinates* center, float angle, coordinates* rotation_center)
{
    coordinates c;
    c.x = center->x;
    c.y = center->y;

    c.x -= rotation_center->x;
    c.y -= rotation_center->y;

    float sn, cs;
    sn = sinf(angle*PI/180.0f);
    cs = cosf(angle*PI/180.0f);

    coordinates rotated;

    rotated.x = cs * c.x - sn * c.y;
    rotated.y = sn * c.x + cs * c.y;

    rotated.x += rotation_center->x;
    rotated.y += rotation_center->y;
    return rotated;
}

coordinates findCenter(SDL_Rect rct, float angle, SDL_Point* rotation_center)
{
    coordinates c;
    c.x = rct.x + rct.w/2;
    c.y = rct.y + rct.h/2;

    if (rotation_center == NULL)
    {
        return c;
    }
    coordinates rc;
    rc.x = rotation_center->x;
    rc.y = rotation_center->y;
    return findCenter(rct, angle, &rc);
}

coordinates findCenter(SDL_Rect rct, float angle, coordinates* rotation_center)
{

    coordinates c, rotated;
    c.x = rct.x + rct.w/2;
    c.y = rct.y + rct.h/2;

    if (rotation_center == NULL)
    {
        return c;
    }
    coordinates rc;
    rc.x = rotation_center->x + rct.x;
    rc.y = rotation_center->y + rct.y;

    rotated = rotatePointByAngle(&c, angle, &rc);

    return rotated;

}

void SaveInFile(string file, string tmp, float value)
{
    string directory = "data\\" + file;
    fstream stream;
    stream.open (directory);
    stream << tmp << " " << value << '\0';
    stream.close ();
}

float LoadFromFile(string file)
{
    float result;
    string tmp;
    string directory = "data\\" + file;
    fstream stream;
    stream.open (directory);
    stream >> tmp >> result;
    stream.close();
    return result;
}

SDL_Texture* LoadTexture(string file, SDL_Renderer* renderer)
{
    SDL_Texture* objectTexture;
    file = "img\\" + file;

    SDL_Surface* loadingSurface = SDL_LoadBMP(file.c_str());
    objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);

    return objectTexture;
}

bool checkForMouseCollision(int mouseX, int mouseY, SDL_Rect object)
{
    if(mouseX > object.x && mouseX < object.x + object.w && mouseY > object.y && mouseY < object.y + object.h)
    {
        return true;
    }
    return false;
}

UIElement* LoadUIElement(string file, SDL_Renderer* render)
{
    UIElement* buff = new UIElement;
    file = "config\\" + file;
    string tmp;
    fstream stream;
    stream.open (file);
    stream >> tmp >> buff->objectRect->w >> buff->objectRect->h >> buff->objectRect->x >> buff->objectRect->y;
    stream >> tmp >> tmp;
    stream.close();
    buff->objectTexture = LoadTexture(tmp, render);
    return buff;
}
