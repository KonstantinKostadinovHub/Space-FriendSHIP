#ifndef PROGRESSSAVER_H
#define PROGRESSSAVER_H

#include <fstream>
using namespace std;

class ProgressSaver
{
    public:
        ProgressSaver();
        virtual ~ProgressSaver();

        void SaveInFile(string file, string tmp, float value);
    protected:

    private:
};

#endif // PROGRESSSAVER_H
