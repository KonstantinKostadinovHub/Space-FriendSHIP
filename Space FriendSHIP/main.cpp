#include<SDL2/SDL.h>
#include "World.h"

using namespace std;


int main (int argc, char* argv[])
{
    World world;
    world.init("config\\world.txt");
    while(true)
    {
        world.update();
        world.draw();
        SDL_Delay(200);
    }
    world.destroy();
    return 0;
}
