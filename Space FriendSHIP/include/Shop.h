#ifndef SHOP_H
#define SHOP_H

#include <fstream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

#include "defines.h"

#include "ConfigManager.h"
#include "UpgradeManager.h"

struct abilityUpgradeStructure
{
    SDL_Texture* abilityImg;
    int level;
    vector<int> prices;
    SDL_Rect frameRect;
    SDL_Rect imgRect;
    coordinates textCoor;
    string name;
};

class Shop
{
public:
    ConfigManager* m_configManager;

    string m_configFile;
    string s_moneyText;

    vector<SDL_Texture*> m_upgradeFrameTexture;
    vector<abilityUpgradeStructure*> m_shopArticles;
    vector<int*> m_upgradeManagerLevels;

    SDL_Renderer* m_renderer;
    SDL_Texture* m_backgroundTexture;
    SDL_Texture* m_backButtonTexture;

    SDL_Rect m_frameRectModel;
    SDL_Rect m_imgRectModel;
    SDL_Rect m_backButton;

    UIElement* m_buttonBack;

    int m_FONT_SIZE;
    int m_spacing;
    int *m_money;
    int *m_mouseX, *m_mouseY;
    int m_numberOfPrices;
    int m_numberOfAbilityUpgrades;

    coordinates m_moneyTextCoor;
    coordinates m_coor;

    bool *m_mouseIsPressed;
    bool *m_quitScene;

    GAME_STATE *m_gameState;

    void init(string configFile, ConfigManager* configManager, SDL_Renderer* renderer, int* mouseX, int* mouseY, bool* mouseIsPressed, int *money, UpgradeManager* um, bool *quitScene, GAME_STATE *gameState);
    void update();
    void draw();

    Shop();
    virtual ~Shop();
};

#endif
