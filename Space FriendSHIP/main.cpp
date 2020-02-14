#include<SDL2/SDL.h>
#include "World.h"

using namespace std;


int main (int argc, char* argv[])
{
    World world;
    world.init("world.txt");
    while(true)
    {
        world.update();
        world.draw();
        SDL_Delay(5);
    }
    world.destroy();
    return 0;
}
