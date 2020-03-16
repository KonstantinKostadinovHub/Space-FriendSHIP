#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SDL2/SDL.h>
#include <string>
#include <fstream>
#include <iostream>


using namespace std;
class HealthBar
{
    public:
        HealthBar();
        virtual ~HealthBar();
         void init(string configFile);
         virtual void update(int health, int maxHealth);
         virtual void draw(SDL_Renderer* renderer);

    protected:
        float HP;
        string m_configFile;
        string m_borderFile;
        string m_healthImgFile;
        SDL_Texture* m_borderTexture;
        SDL_Texture* m_healthTexture;
        SDL_Rect m_objRect;

    private:
};

#endif // HEALTHBAR_H
