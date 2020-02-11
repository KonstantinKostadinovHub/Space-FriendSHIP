#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include<SDL2/SDL.h>

#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"
#include "Artefact.h"

#include "Rock.h"

using namespace std;

class World
{
    public:
        World();
        virtual ~World();

        SDL_Window* m_main_window = NULL;
        SDL_Renderer* m_main_renderer = NULL;

        string m_configFile;

        int m_SCREEN_WIDTH;
        int m_SCREEN_HEIGHT;
        string m_backgroundImg;
        vector<Player*> m_players;
        vector<Enemy*> m_enemies;
        vector<Projectile*> m_projectiles;
        vector<Artefact*> m_artefacts;
        SDL_Texture* m_backgroundTexture;

        void init(string configFile);
        void destroy();
        void update();
        void draw();
        void addEnemy(string configFile, int x, int y);
        void cleaner();
        bool checkForCollisionBetweenObjects(SDL_Rect rect1, SDL_Rect rect2);
    protected:

    private:
};

#endif // WORLD_H
