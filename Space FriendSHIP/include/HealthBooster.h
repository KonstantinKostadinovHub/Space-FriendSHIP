#ifndef HEALTHBOOSTER_H
#define HEALTHBOOSTER_H
#include "Artefact.h"

#include <fstream>

class HealthBooster : public Artefact
{
    public:
        HealthBooster();
        virtual ~HealthBooster();
        virtual void init(string configFile, coordinates coor, coordinates direction);
        string tmp;

    protected:

    private:
};

#endif // HEALTHBOOSTER_H

