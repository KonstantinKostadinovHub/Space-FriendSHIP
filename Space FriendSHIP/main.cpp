#include <SDL2/SDL.h>

#include "World.h"

using namespace std;

World world;

int main (int argc, char* argv[])
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    const Uint8 *state2 = SDL_GetKeyboardState(NULL);

    world.init("world.txt");
    world.m_gameState = MENU;

    while(true)
    {
        if(world.m_gameState == MENU)
        {
            while(!world.m_quitScene)
            {
                world.input();
                world.m_menu->update();
                world.m_menu->draw();
                SDL_Delay(20);
            }
            world.m_quitScene = false;
        }
        if(world.m_gameState == TUTORIAL)
        {
            while(!world.m_quitScene)
            {
                world.input();
                world.tutorial();
                SDL_Delay(20);
            }
            world.m_quitScene = false;
        }
        if(world.m_gameState == EXIT)
        {
            while(!world.m_quitScene)
            {
                world.input();
                world.destroy();
                SDL_Delay(20);
            }
            world.m_quitScene = false;
        }
        if(world.m_gameState == SHOP)
        {
            world.loadProgress();
            while(!world.m_quitScene)
            {
                world.input();
                world.shop();
            }
            world.saveProgress();
            world.m_quitScene = false;
        }
        if(world.m_gameState == GAME_SINGLEPLAYER || world.m_gameState == GAME_MULTIPLAYER)
        {
            world.initSession();
            world.chooseGameMode();
            world.loadProgress();
            while(!world.m_quitScene)
            {
                world.input();
                world.update();
                world.draw();
                world.cleaner();
                SDL_Delay(17);
            }
            world.m_quitScene = false;
            world.saveProgress();
        }
        if(world.m_gameState == DIED)
        {
            world.endgameScreen();
            SDL_Delay(8000);
            world.destroySession();
            world.m_gameState = MENU;
            world.m_quitScene = false;
        }
    }
    return 0;
}
