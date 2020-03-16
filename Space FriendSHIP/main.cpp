#include <SDL2/SDL.h>

#include "World.h"

using namespace std;

World world;

int main (int argc, char* argv[])
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    const Uint8 *state2 = SDL_GetKeyboardState(NULL);
    while(1){
        world.init("world.txt");
        world.endgame = false;
        bool quit = false;

        //world.addPlayer(world.m_main_renderer, "player1.txt");
        world.addPlayer(world.m_main_renderer, "player2.txt");

        SDL_Event e;

        while(quit!=true)
        {

            while(SDL_PollEvent(&e) == 0)
            {
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
            while(SDL_PollEvent(&e) == 0)
            {
                world.update();
                world.draw();
                world.cleaner();
                SDL_Delay(20);
            }
        }
        SDL_Delay(500);
        world.endgameScreen();
        SDL_Delay(8000);
        world.destroy();
    }

    return 0;
}
