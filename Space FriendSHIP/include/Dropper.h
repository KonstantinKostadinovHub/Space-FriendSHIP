#ifndef DROPPER_H
#define DROPPER_H

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Engine.h"

class Dropper
{
    public:
        Dropper();
        virtual ~Dropper();
        string m_configName;
        int m_healthProb;
        int m_speedProb;
        vector <string> m_probabilities;

        string m_type;
        string tmp;
        coordinates m_coor;
        coordinates m_direction;

        void init(string configName);
        void spawn(int SCREEN_WIDTH, int SCREEN_HEIGHT);
    protected:

    private:
};
#endif // DROPPER_H
