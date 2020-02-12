#include<SDL2/SDL.h>
#include "World.h"

using namespace std;


int main (int argc, char* argv[])
{
    World world;
    world.init("world.txt");
    world.addEnemy("rock.txt", 0, 559, 1, -0.9);
    while(true)
    {
        world.update();
        world.draw();
        SDL_Delay(5);
    }
    world.destroy();
    return 0;
}
