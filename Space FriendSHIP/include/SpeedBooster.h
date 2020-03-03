#ifndef SPEEDBOOSTER_H
#define SPEEDBOOSTER_H

#include "Artefact.h"

#include <fstream>

class SpeedBooster: public Artefact
{
    public:
        SpeedBooster();
        virtual ~SpeedBooster();
        virtual void init(string configFile, coordinates coor, coordinates direction);
        string tmp;

    protected:

    private:
};

#endif // SPEEDBOOSTER_H
