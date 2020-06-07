#ifndef WRITER_H
#define WRITER_H

#include "Engine.h"
#include <SDL2/SDL.h>
#include <string>
#include <fstream>

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

        SDL_Renderer* m_renderer = NULL;

        string tmp;
        string m_configFile;

        int *m_points;
        int *m_highScore;

        void WriteFPS();
        void WriteScore();
        void WritePlayer1();
        void WritePlayer2();
        void WriteHighScore();
        void init(string configFile, SDL_Renderer* renderer, int *points, int *highScore);

    protected:

    private:
};

#endif // WRITER_H
