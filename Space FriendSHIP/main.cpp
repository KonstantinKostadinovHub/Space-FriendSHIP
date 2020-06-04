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
                SDL_Delay(15);
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

    /*
    world.m_lastFrame = SDL_GetTicks();
            if(world.m_lastFrame >= (world.m_lastTime+1000))
            {
                world.m_lastTime=world.m_lastFrame;
                world.m_fps=world.m_frameCount;
                world.m_frameCount=0;
            }
    */
    return 0;
}
