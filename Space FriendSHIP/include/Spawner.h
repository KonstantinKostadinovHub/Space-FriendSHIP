#ifndef SPAWNER_H
#define SPAWNER_H

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Engine.h"

using namespace std;

class Spawner
{
public:
    Spawner();
    virtual ~Spawner();

    string m_configName;
    int m_rockProb;
    string m_type;
    vector<string> m_probabilities;

    coordinates m_coor;
    coordinates m_direction;

    void init(string configName);
    void spawn(int SCREEN_WIDTH, int SCREEN_HEIGHT);

protected:

private:
};

#endif // SPAWNER_H
