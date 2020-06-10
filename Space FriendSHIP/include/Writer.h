#ifndef WRITER_H
#define WRITER_H

#include <SDL2/SDL.h>
#include <string>
#include <fstream>

#include "Engine.h"

class Writer
{
public:
    Writer();
    virtual ~Writer();

    int CoorFPSX, CoorFPSY;
    int CoorPlayer1X, CoorPlayer1Y;
    int CoorScoreX, CoorScoreY;
    int CoorScoreTextX, CoorScoreTextY;
    int CoorPlayer2X, CoorPlayer2Y;
    int CoorHighScoreX, CoorHighScoreY;
    int *m_points;
    int *m_highScore;

    SDL_Renderer* m_renderer = NULL;

    string m_configFile;

    void WriteFPS();
    void WriteScore();
    void WritePlayer1();
    void WritePlayer2();
    void WriteHighScore();
    void init(string configFile, SDL_Renderer* renderer, int *points, int *highScore);
};

#endif
