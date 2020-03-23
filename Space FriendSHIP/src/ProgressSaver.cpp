#include "ProgressSaver.h"

ProgressSaver::ProgressSaver()
{
    //ctor
}

ProgressSaver::~ProgressSaver()
{
    //dtor
}

void ProgressSaver::SaveInFile(string file, string tmp, float value)
{
    string directory = "data\\" + file;
    fstream stream;
    stream.open (directory);
    stream << tmp << " " << value;
    stream.close ();
}
