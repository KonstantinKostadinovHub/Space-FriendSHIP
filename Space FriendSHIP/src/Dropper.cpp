#include "Dropper.h"

Dropper::Dropper()
{
    //ctor
}

Dropper::~Dropper()
{
    //dtor
}

void Dropper::init(string configName)
{
    m_configName = "config\\";
    m_configName += configName;

    fstream stream;
    string tmp;

    stream.open(m_configName.c_str());

    stream >> tmp >> m_healthProb;
    stream >> tmp >> m_speedProb;
    stream >> tmp >> m_stopProb;
    stream >> tmp >> m_reverseProb;
    stream >> tmp >> m_coinProb;
    stream >> tmp >> m_shieldProb;

    for(int i = 0; i < m_healthProb ; i++)
    {
        m_probabilities.push_back("healthbooster.txt");
    }
    for(int i = 0; i < m_speedProb ; i++)
    {
        m_probabilities.push_back("speedbooster.txt");
    }
    for(int i = 0; i < m_stopProb; i++)
    {
        m_probabilities.push_back("stopper.txt");
    }
    for(int i = 0; i < m_reverseProb; i++)
    {
        m_probabilities.push_back("reverser.txt");
    }
    for(int i = 0; i < m_coinProb; i++)
    {
        m_probabilities.push_back("coin.txt");
    }
    for(int i = 0; i < m_shieldProb; i++)
    {
        m_probabilities.push_back("shield.txt");
    }

    stream.close();
}

void Dropper::spawn(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    coordinates spawn;
    int multiplayer;

    if(rand() % 2 == 0)
    {
        multiplayer = 1;
    }
    else
    {
        multiplayer = -1;
    }

    coordinates direction;

    switch(rand() % 4)
    {
    case 0:
        spawn.x = rand() % (SCREEN_WIDTH - 64);
        spawn.y = 0;
        direction.x = (float(rand() % 9) * 0.1 + 0.1) * multiplayer;
        direction.y = 1;
        break;
    case 1:
        spawn.x = rand() % (SCREEN_WIDTH - 64);
        spawn.y = SCREEN_HEIGHT - 64;
        direction.x = (float(rand() % 9) * 0.1 + 0.1) * multiplayer;
        direction.y = -1;
        break;
    case 2:
        spawn.x = 0;
        spawn.y = rand() % (SCREEN_HEIGHT - 64);
        direction.x = 1;
        direction.y = (float(rand() % 9) * 0.1 + 0.1) * multiplayer;
        break;
    case 3:
        spawn.x = SCREEN_WIDTH - 64;
        spawn.y = rand() % (SCREEN_HEIGHT - 64);
        direction.x = -1;
        direction.y = (float(rand() % 9) * 0.1 + 0.1) * multiplayer;
        break;
    }

    m_type = m_probabilities[rand() % m_probabilities.size()];
    m_coor.x = spawn.x;
    m_coor.y = spawn.y;
    m_direction.x = direction.x;
    m_direction.y = direction.y;
}
