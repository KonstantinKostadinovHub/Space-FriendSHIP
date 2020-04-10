#include "Shop.h"

Shop::Shop()
{

}

Shop::~Shop()
{
    //dtor
}

void Shop::init(string configFile, ConfigManager* configManager, SDL_Renderer* renderer, int *mouseX, int *mouseY, bool *mouseIsPressed, int *money)
{
    m_configManager = configManager;

    m_renderer = renderer;

    m_configFile = "config\\" + configFile;

    m_mouseX = mouseX;
    m_mouseY = mouseY;
    m_mouseIsPressed = mouseIsPressed;
    m_money = money;

    fstream stream;

    int intBuff;
    string stringBuff;
    string tmp;

    stream.open(m_configFile.c_str());
    stream >> tmp >> intBuff;
    m_spacing = intBuff;
    stream >> tmp >> m_frameRectModel.w >> m_frameRectModel.h;
    stream >> tmp >> m_imgRectModel.w >> m_imgRectModel.h;
    stream >> tmp >> m_coor.x >> m_coor.y;
    stream >> tmp >> stringBuff;
    m_backgroundTexture = LoadTexture(stringBuff, m_renderer);
    stream >> tmp >> intBuff;
    m_numberOfPrices = intBuff;
    stream >> tmp >> intBuff;
    m_numberOfAbilityUpgrades = intBuff;

    for(int i = 0; i < m_numberOfAbilityUpgrades; i++)
    {
        abilityUpgradeStructure* abilityUpgrade = new abilityUpgradeStructure;
        stream >> stringBuff;
        abilityUpgrade->abilityImg = LoadTexture(stringBuff, m_renderer);
        abilityUpgrade->level = 0;
        abilityUpgrade->frameRect = m_frameRectModel;
        abilityUpgrade->imgRect = m_imgRectModel;
        abilityUpgrade->frameRect.x = m_coor.x + (i % 4) * (m_frameRectModel.w + m_spacing);
        abilityUpgrade->frameRect.y = m_coor.y + (i / 4) * (m_frameRectModel.h + m_spacing);
        abilityUpgrade->imgRect.x = abilityUpgrade->frameRect.x + 4;
        abilityUpgrade->imgRect.y = abilityUpgrade->frameRect.y + 4;

        for(int j = 0; j < m_numberOfPrices; j++)
        {
            stream >> intBuff;
            abilityUpgrade->prices.push_back(intBuff);
        }

        m_shopArticles.push_back(abilityUpgrade);

    }
    stream >> tmp >> intBuff;
    for(int i = 0; i < intBuff; i++)
    {
        stream >> stringBuff;
        m_upgradeFrameTexture.push_back(LoadTexture(stringBuff, m_renderer));
    }
    stream.close();

}

void Shop::update()
{
    if(*m_mouseIsPressed){
        for(int i = 0; i < m_shopArticles.size(); i++)
        {
            if(checkForMouseCollision(*m_mouseX, *m_mouseY, m_shopArticles[i]->frameRect) && m_shopArticles[i]->level < 8 && m_shopArticles[i]->prices[m_shopArticles[i]->level] <= *m_money)
            {
                *m_money -= m_shopArticles[i]->prices[m_shopArticles[i]->level];
                m_shopArticles[i]->level++;
            }
        }
    }
}

void Shop::draw()
{
    SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, NULL);
    for(int i = 0; i < m_shopArticles.size(); i++)
    {
        SDL_RenderCopy(m_renderer, m_shopArticles[i]->abilityImg, NULL, &(m_shopArticles[i]->imgRect));
        SDL_RenderCopy(m_renderer, m_upgradeFrameTexture[m_shopArticles[i]->level], NULL, &(m_shopArticles[i]->frameRect));
    }
    SDL_RenderPresent(m_renderer);
}
