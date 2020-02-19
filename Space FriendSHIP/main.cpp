#include<SDL2/SDL.h>
#include "World.h"

using namespace std;


int main (int argc, char* argv[])
{
    bool quit=false;
    World world;
    world.init("world.txt");
    SDL_Event e;

    while(quit!=true)
    {

        while(SDL_PollEvent(&e)==0)
        {
            const Uint8 *state2 = SDL_GetKeyboardState(NULL);
            world.menu();
            SDL_Delay(5);
            if (state2[SDL_SCANCODE_RETURN])
            {
                quit = true;
            }
        }
        SDL_Delay(30);
    }
    while(world.endgame == false)
    {
        world.update();
        world.draw();
        world.cleaner();
        SDL_Delay(5);
        //} while (SDL_PollEvent(&e)==0);
    }
    world.endgameScreen();
    SDL_Delay(5000);
    world.destroy();
    return 0;
}
