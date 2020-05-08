#include "Engine.h"

#include <SDL2/SDL_ttf.h>

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

bool checkIfOffBounds(SDL_Rect rect, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    if (rect.x + rect.w > SCREEN_WIDTH)
        return true;
    if (rect.x < 0)
        return true;
    if (rect.y + rect.h > SCREEN_HEIGHT)
        return true;
    if (rect.y < 0)
        return true;
    return false;
}

bool checkForCollisionBetweenObjects(SDL_Rect rect_no_rotation1, float angle1, SDL_Point* center1,
                                     SDL_Rect rect_no_rotation2, float angle2, SDL_Point* center2)
{
    bool colide = false;
    coordinates c1, c2;

    c1 = findCenter(rect_no_rotation1, angle1, center1);
    c2 = findCenter(rect_no_rotation2, angle2, center2);

    float a_2 = (c1.x - c2.x)*(c1.x - c2.x);
    float b_2 = (c1.y - c2.y)*(c1.y - c2.y);
    float c   = hypot(rect_no_rotation1.h,rect_no_rotation1.w)/2 +
                hypot(rect_no_rotation2.h,rect_no_rotation2.w)/2;

    return (a_2 + b_2 <= c*c/2);
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

void write(string text, coordinates coor, SDL_Renderer* renderer, int FONT_SIZE) {
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect rect;
    SDL_Color fcolor;
    TTF_Font* font;

    string str = "ttf/Roboto-Regular.ttf";
    font = TTF_OpenFont(str.c_str(), FONT_SIZE);

    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    fcolor.r = 255;
    fcolor.g = 255;
    fcolor.b = 255;
    const char* t = text.c_str();
    surface = TTF_RenderText_Solid(font, t, fcolor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = coor.x-rect.w;
    rect.y = coor.y-rect.h;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
