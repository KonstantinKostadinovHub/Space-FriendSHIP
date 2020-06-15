#include "Menu.h"

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::load(string configFile, SDL_Renderer* renderer,int *mouseX, int *mouseY, bool *mouseIsPressed, bool *quit, GAME_STATE* gameState, SDL_Texture* backgroundTexture)
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
    m_backgroundTexture = backgroundTexture;

    stream.open(configFile.c_str());
    stream >> tmp >> backgroundImg;
    stream >> tmp >> m_SingleplayerButton.x >> m_SingleplayerButton.y >> m_SingleplayerButton.w >> m_SingleplayerButton.h;
    stream >> tmp >> m_MultiplayerButton.x >> m_MultiplayerButton.y >> m_MultiplayerButton.w >> m_MultiplayerButton.h;
    stream >> tmp >> m_ShopButton.x >> m_ShopButton.y >> m_ShopButton.w >> m_ShopButton.h;
    stream >> tmp >> m_TutorialButton.x >> m_TutorialButton.y >> m_TutorialButton.w >> m_TutorialButton.h;
    stream >> tmp >> m_ExitButton.x >> m_ExitButton.y >> m_ExitButton.w >> m_ExitButton.h;
    stream.close();

    m_menuTexture = LoadTexture(backgroundImg, m_renderer);
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
        if(checkForMouseCollision(*m_mouseX, *m_mouseY, m_TutorialButton))
        {
            (*m_gameState) = TUTORIAL;
            (*m_quitScene) = true;
        }
        if(checkForMouseCollision(*m_mouseX, *m_mouseY, m_ExitButton))
        {
            (*m_gameState) = EXIT;
            (*m_quitScene) = true;
        }
    }
}

void Menu::draw()
{
    SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, NULL);
    SDL_RenderCopy(m_renderer, m_menuTexture, NULL, NULL);

    SDL_RenderPresent(m_renderer);
}
