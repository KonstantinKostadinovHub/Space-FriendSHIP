#include <SDL2/SDL.h>

#include "World.h"

using namespace std;

World world;

int main (int argc, char* argv[])
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    const Uint8 *state2 = SDL_GetKeyboardState(NULL);

    world.init("world.txt");
    while(1)
    {
        world.initSession();
        world.endgame = false;
        bool quit = false;

        SDL_Event e;

        while(quit!=true)
        {
            world.m_lastFrame = SDL_GetTicks();
            if(world.m_lastFrame >= (world.m_lastTime+1000))
            {
                world.m_lastTime=world.m_lastFrame;
                world.m_fps=world.m_frameCount;
                world.m_frameCount=0;
            }

            while(SDL_PollEvent(&e) == 0)
            {

                world.menu();
                SDL_Delay(5);

                if ((world.m_menuImg != world.m_menuImg1) && (state[SDL_SCANCODE_RETURN]))
                {
                    quit = true;
                }
            }
        }
        world.loadProgress();
        cout << world.m_highScore << " sakdfsdnv" << endl;
/*
        while(true)
        {
        world.m_lastFrame=SDL_GetTicks();
        if(world.m_lastFrame>=(world.m_lastTime+1000)) {
            world.m_lastTime=world.m_lastFrame;
            world.m_fps=world.m_frameCount;
            world.m_frameCount=0;
        }

              while(SDL_PollEvent(&e) == 0)
              {
                  SDL_Delay(5);
                  if(e.type == SDL_MOUSEMOTION)
                  {
                      SDL_GetGlobalMouseState(&(world.mouseX), &(world.mouseY));
                  }
                  world.mouseIsPressed = false;
                  if(e.type == SDL_MOUSEBUTTONDOWN)
                  {
                      world.mouseIsPressed = true;
                      e.type = SDLK_UNKNOWN;
                  }
                  world.m_shop->m_mouseIsPressed = world.mouseIsPressed;
                  world.shop();
              }
          }
*/
        world.chooseGameMode();
        world.loadProgress();

        while(world.endgame == false)
        {
            world.m_lastFrame=SDL_GetTicks();
            if(world.m_lastFrame>=(world.m_lastTime+1000)) {
                world.m_lastTime=world.m_lastFrame;
                world.m_fps=world.m_frameCount;
                world.m_frameCount=0;
            }

            while(SDL_PollEvent(&e) == 0)
            {
                world.update();
                world.draw();
                world.cleaner();
                if(world.endgame)
                    break;
                SDL_Delay(20);
            }
        }
        world.saveProgress();
        world.loadProgress();
        SDL_Delay(500);
        world.endgameScreen();
        SDL_Delay(8000);
        world.destroySession();
    }
    world.destroy();

    return 0;
}
