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

    stream >> tmp >> m_rockProb;
    stream >> tmp >> m_shooterDefaultProb;
    stream >> tmp >> m_shooterSniperProb;
    stream >> tmp >> m_shooterSMGProb;
    stream >> tmp >> m_shooterTankProb;
    stream >> tmp >> m_zigZagProb;

    for(int i = 0; i < m_rockProb ; i++)
    {
        m_probabilities.push_back("rock.txt");
    }
    for(int i = 0; i < m_shooterDefaultProb ; i++)
    {
        m_probabilities.push_back("shooter_default.txt");
    }
    for(int i = 0; i < m_shooterSniperProb ; i++)
    {
        m_probabilities.push_back("shooter_sniper.txt");
    }
    for(int i = 0; i < m_shooterSMGProb ; i++)
    {
        m_probabilities.push_back("shooter_smg.txt");
    }
    for(int i = 0; i < m_shooterTankProb ; i++)
    {
        m_probabilities.push_back("shooter_tank.txt");
    }
    for(int i = 0; i < m_zigZagProb ; i++)
    {
        m_probabilities.push_back("zigzag.txt");
    }
    stream.close();
}

void Spawner::spawn(int SCREEN_WIDTH, int SCREEN_HEIGHT)
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

