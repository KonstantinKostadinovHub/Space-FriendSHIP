#ifndef SPAWNER_H
#define SPAWNER_H

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

        int m_x;
        int m_y;
        float m_directionX;
        float m_directionY;

        void init(string configName);
        void spawn(int SCREEN_WIDTH, int SCREEN_HEIGHT);

    protected:

    private:
};

#endif // SPAWNER_H
