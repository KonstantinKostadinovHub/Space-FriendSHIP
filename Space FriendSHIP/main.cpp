#include <SDL2/SDL.h>

#include "World.h"

using namespace std;

World world;

int main (int argc, char* argv[])
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    const Uint8 *state2 = SDL_GetKeyboardState(NULL);

    while(1)
    {
        world.init("world.txt");
        world.endgame = false;
        bool quit = false;

        SDL_Event e;

        while(quit!=true)
        {

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
        /*while(true)
          {
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
                  world.shop();
              }
          }
        */
        world.chooseGameMode();
        world.loadProgress();
        while(world.endgame == false)
        {
            while(SDL_PollEvent(&e) == 0)
            {
                world.update();
                world.draw();
                world.cleaner();
                SDL_Delay(20);
            }
        }
        world.saveProgress();
        SDL_Delay(500);
        world.endgameScreen();
        SDL_Delay(8000);
        world.destroy();
    }

    return 0;
}
