#include "Menu.h"

Menu::Menu()
{
    //ctor
}

Menu::~Menu()
{
    //dtor
}

void Menu::load(string configFile, SDL_Renderer* renderer,int *mouseX, int *mouseY, bool *mouseIsPressed, bool *quit, GAME_STATE* gameState)
{
    configFile = "config\\" + configFile;
    fstream stream;
    string tmp, backgroundImg;

    m_renderer = renderer;
    m_mouseIsPressed = mouseIsPressed;
    m_mouseX = mouseX;
    m_mouseY = mouseY;
    m_quitScene = quit;
    m_gameState = gameState;

    stream.open(configFile.c_str());
    stream >> tmp >> backgroundImg;
    stream >> tmp >> m_SingleplayerButton.x >> m_SingleplayerButton.y >> m_SingleplayerButton.w >> m_SingleplayerButton.h;
    stream >> tmp >> m_MultiplayerButton.x >> m_MultiplayerButton.y >> m_MultiplayerButton.w >> m_MultiplayerButton.h;
    stream >> tmp >> m_ShopButton.x >> m_ShopButton.y >> m_ShopButton.w >> m_ShopButton.h;
    stream.close();

    m_backgroundTexture = LoadTexture(backgroundImg, m_renderer);
}

void Menu::update()
{
    if((*m_mouseIsPressed))
    {
        if(checkForMouseCollision(*m_mouseX, *m_mouseY, m_SingleplayerButton))
        {
            (*m_gameState) = GAME_SINGLEPLAYER;
            (*m_quitScene) = true;
        }
        if(checkForMouseCollision(*m_mouseX, *m_mouseY, m_MultiplayerButton))
        {
            (*m_gameState) = GAME_MULTIPLAYER;
            (*m_quitScene) = true;
        }
        if(checkForMouseCollision(*m_mouseX, *m_mouseY, m_ShopButton))
        {
            (*m_gameState) = SHOP;
            (*m_quitScene) = true;
        }
    }
    ///cout << *m_mouseX << " " << *m_mouseY << endl;
}

void Menu::draw()
{
    SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, NULL);

    SDL_RenderPresent(m_renderer);
}
