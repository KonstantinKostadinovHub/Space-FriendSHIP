#include<SDL2/SDL.h>
#include "World.h"

using namespace std;


int main (int argc, char* argv[])
{
    World world;
    world.init("world.txt");
    world.addEnemy("rock.txt", 50, 50);
    while(true)
    {
        world.update();
        world.draw();
    }
    world.destroy();
    return 0;
}
