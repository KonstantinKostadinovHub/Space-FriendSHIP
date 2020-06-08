#ifndef MENU_H
#define MENU_H

#include <cstring>
#include <fstream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "defines.h"

#include "Engine.h"

using namespace std;

class Menu
{
    public:
        Menu();
        virtual ~Menu();

        SDL_Texture* m_backgroundTexture;
        SDL_Rect m_SingleplayerButton;
        SDL_Rect m_MultiplayerButton;
        SDL_Rect m_ShopButton;
        SDL_Rect m_TutorialButton;
        SDL_Renderer* m_renderer;

        int *m_mouseX, *m_mouseY;
        bool *m_mouseIsPressed;
        bool *m_quitScene;
        GAME_STATE *m_gameState;

        void load(string configFile, SDL_Renderer* renderer,int *mouseX, int *mouseY, bool *mouseIsPressed, bool *quit, GAME_STATE* gameState);
        void update();
        void draw();
    protected:

    private:
};

#endif // MENU_H
