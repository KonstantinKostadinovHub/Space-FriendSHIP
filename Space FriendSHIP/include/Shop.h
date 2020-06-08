#ifndef SHOP_H
#define SHOP_H

#include <fstream>
#include <vector>
#include <string>

#include <SDL2/SDL.h>

#include "defines.h"

#include <ConfigManager.h>
#include <UpgradeManager.h>

struct abilityUpgradeStructure
{
    SDL_Texture* abilityImg;
    int level;
    vector<int> prices;
    SDL_Rect frameRect;
    SDL_Rect imgRect;
};

class Shop
{
    public:
        ConfigManager* m_configManager;

        string m_configFile;

        vector<SDL_Texture*> m_upgradeFrameTexture;

        SDL_Renderer* m_renderer;
        SDL_Texture* m_backgroundTexture;
        SDL_Texture* m_backButtonTexture;
        UIElement* m_buttonBack;

        string s_moneyText;
        int m_FONT_SIZE;
        coordinates m_moneyTextCoor;

        vector<abilityUpgradeStructure*> m_shopArticles;

        coordinates m_coor;
        int m_spacing;
        SDL_Rect m_frameRectModel;
        SDL_Rect m_imgRectModel;
        SDL_Rect m_backButton;
        int *m_mouseX, *m_mouseY;
        bool *m_mouseIsPressed;
        int *m_money;
        bool *m_quitScene;
        GAME_STATE *m_gameState;

        int m_numberOfPrices;
        int m_numberOfAbilityUpgrades;
        vector<int*> m_upgradeManagerLevels;

        void init(string configFile, ConfigManager* configManager, SDL_Renderer* renderer, int* mouseX, int* mouseY, bool* mouseIsPressed, int *money, UpgradeManager* um, bool *quitScene, GAME_STATE *gameState);
        void update();
        void draw();

        Shop();
        virtual ~Shop();

    protected:

    private:
};

#endif // SHOP_H
