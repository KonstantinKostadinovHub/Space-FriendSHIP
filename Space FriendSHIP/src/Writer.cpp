#include "Writer.h"

Writer::Writer()
{
    //ctor
}

Writer::~Writer()
{
    //dtor
}

void Writer::init(string configFile, SDL_Renderer* renderer, int *points, int *highScore)
{
    m_configFile = "config\\" + configFile;
    fstream stream;

    stream.open(m_configFile.c_str());

    stream >> tmp >> CoorScoreX >> CoorScoreY;
    stream >> tmp >> CoorScoreTextX >> CoorScoreTextY;
    stream >> tmp >> CoorPlayer1X >> CoorPlayer1Y;
    stream >> tmp >> CoorPlayer2X >> CoorPlayer2Y;
    stream >> tmp >> CoorHighScoreX >> CoorHighScoreY;
    stream.close();

    m_points = points;
    m_highScore = highScore;
    m_renderer = renderer;
}

void Writer::WriteScore()
{
    coordinates CoorScore;
    coordinates CoorScoreText;

    CoorScore.x = CoorScoreX;
    CoorScore.y = CoorScoreY;

    CoorScoreText.x = CoorScoreTextX;
    CoorScoreText.y =  CoorScoreTextY;

    write("Score: ", CoorScoreText, m_renderer, 30);
    write(to_string(*m_points), CoorScore, m_renderer, 25);
}

void Writer::WritePlayer1()
{
    coordinates CoorPlayer1;

    CoorPlayer1.x = CoorPlayer1X;
    CoorPlayer1.y = CoorPlayer1Y;

    write("Player 1:", CoorPlayer1, m_renderer, 25);
}

void Writer::WritePlayer2()
{
    coordinates CoorPlayer2;

    CoorPlayer2.x = CoorPlayer2X;
    CoorPlayer2.y = CoorPlayer2Y;

    write("Player 2:", CoorPlayer2, m_renderer, 25);
}

void Writer::WriteHighScore()
{
    coordinates CoorHighScore;

    CoorHighScore.x = CoorHighScoreX;
    CoorHighScore.y = CoorHighScoreY;

    write("High Score: " + to_string(*m_highScore), CoorHighScore, m_renderer, 35);
}
