#include "Spawner.h"

Spawner::Spawner()
{
    //ctor
}

Spawner::~Spawner()
{
    //dtor
}

void Spawner::init(string configName)
{
    m_configName = "config\\" + configName;
    fstream stream;
    stream.open(m_configName.c_str());
    stream >> m_rockProb;
    for(int i = 0; i < m_rockProb ; i++)
    {
        m_probabilities.push_back("rock.txt");
    }
    stream.close();
}

void Spawner::spawn(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    int spawnX, spawnY;
    int multiplayer;
    if(rand() % 2 == 0)
    {
        multiplayer = 1;
    }else{
        multiplayer = -1;
    }
    float directionX, directionY;
    switch(rand() % 4){
    case 0:
        spawnX = rand() % (SCREEN_WIDTH - 64);
        spawnY = 0;
        directionX = (float(rand() % 9) * 0.1 + 0.1) * multiplayer;
        directionY = 1;
        break;
    case 1:
        spawnX = rand() % (SCREEN_WIDTH - 64);
        spawnY = SCREEN_HEIGHT - 64;
        directionX = (float(rand() % 9) * 0.1 + 0.1) * multiplayer;
        directionY = -1;
        break;
    case 2:
        spawnX = 0;
        spawnY = rand() % (SCREEN_HEIGHT - 64);
        directionX = 1;
        directionY = (float(rand() % 9) * 0.1 + 0.1) * multiplayer;
        break;
    case 3:
        spawnX = SCREEN_WIDTH - 64;
        spawnY = rand() % (SCREEN_HEIGHT - 64);
        directionX = -1;
        directionY = (float(rand() % 9) * 0.1 + 0.1) * multiplayer;
        break;
    }
    m_type = m_probabilities[rand() % m_probabilities.size()];
    m_x = spawnX;
    m_y = spawnY;
    m_directionX = directionX;
    m_directionY = directionY;
}
