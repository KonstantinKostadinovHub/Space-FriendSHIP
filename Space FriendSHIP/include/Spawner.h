#ifndef SPAWNER_H
#define SPAWNER_H

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Engine.h"

class Spawner
{
public:
    Spawner();
    virtual ~Spawner();

    string m_type;
    string m_configName;
    string tmp;

    int m_rockProb;
    int m_shooterDefaultProb;
    int m_shooterSniperProb;
    int m_shooterTankProb;
    int m_shooterSMGProb;
    int m_zigZagProb;

    vector <string> m_probabilities;

    coordinates m_coor;
    coordinates m_direction;

    void init(string configName);
    void spawn(int SCREEN_WIDTH, int SCREEN_HEIGHT);

protected:

private:
};

#endif // SPAWNER_H

