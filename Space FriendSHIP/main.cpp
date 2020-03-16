#include <SDL2/SDL.h>

#include "World.h"

using namespace std;

World world;

int main (int argc, char* argv[])
{
    world.init("world.txt");
    bool quit = false;

     world.addPlayer(world.m_main_renderer, "player1.txt");
     //world.addPlayer(world.m_main_renderer, "player2.txt");

    SDL_Event e;
    while(quit!=true)
    {

        while(SDL_PollEvent(&e) == 0)
        {
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            world.menu();
            SDL_Delay(5);
            if (state[SDL_SCANCODE_RETURN])
            {
                quit = true;
            }
        }
    }

    while(world.endgame == false)
    {
        while(SDL_PollEvent(&e) == 0){
            world.update();
            world.draw();
            world.cleaner();
            SDL_Delay(20);
        }
    }

    world.endgameScreen();
    SDL_Delay(5000);
    world.destroy();

    return 0;
}
