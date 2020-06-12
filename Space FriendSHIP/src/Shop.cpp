#include "Shop.h"

Shop::Shop()
{

}

Shop::~Shop()
{

}

void Shop::init(string configFile, ConfigManager* configManager, SDL_Renderer* renderer, int* mouseX, int* mouseY, bool* mouseIsPressed, int *money, UpgradeManager* um, bool *quitScene, GAME_STATE *gameState)
{
    m_configManager = configManager;

    m_renderer = renderer;

    m_configFile = "config\\" + configFile;

    m_mouseX = mouseX;
    m_mouseY = mouseY;
    m_mouseIsPressed = mouseIsPressed;
    m_money = money;
    m_quitScene = quitScene;
    m_gameState = gameState;

    fstream stream;

    int intBuff;
    string stringBuff;
    string tmp;
    coordinates coorBuff;

    m_upgradeManagerLevels.push_back(&(um->m_CurrentLevelHealthUpgrade));
    m_upgradeManagerLevels.push_back(&(um->m_CurrentLevelCoinsMultiplierUpgrade));
    m_upgradeManagerLevels.push_back(&(um->m_CurrentLevelDashUpgrade));
    m_upgradeManagerLevels.push_back(&(um->m_CurrentLevelCollisionDamageUpgrade));
    m_upgradeManagerLevels.push_back(&(um->m_CurrentLevelHealthBoosterUpgrade));
    m_upgradeManagerLevels.push_back(&(um->m_CurrentLevelBulletDamageUpgrade));

    stream.open(m_configFile.c_str());
    stream >> tmp >> m_moneyTextCoor.x >> m_moneyTextCoor.y;
    stream >> tmp >> m_FONT_SIZE;
    stream >> tmp >> s_moneyText;
    stream >> tmp >> m_spacing;
    stream >> tmp >> m_frameRectModel.w >> m_frameRectModel.h;
    stream >> tmp >> coorBuff.x >> coorBuff.y;
    stream >> tmp >> m_imgRectModel.w >> m_imgRectModel.h;
    stream >> tmp >> m_coor.x >> m_coor.y;
    stream >> tmp >> stringBuff;
    m_backgroundTexture = LoadTexture(stringBuff, m_renderer);
    stream >> tmp >> stringBuff;
    m_backButtonTexture = LoadTexture(stringBuff, m_renderer);
    stream >> tmp >> m_backButton.x >> m_backButton.y >> m_backButton.w >> m_backButton.h;
    stream >> tmp >> m_numberOfPrices;
    stream >> tmp >> m_numberOfAbilityUpgrades;

    for(int i = 0; i < m_numberOfAbilityUpgrades; i++)
    {
        abilityUpgradeStructure* abilityUpgrade = new abilityUpgradeStructure;
        stream >> stringBuff;
        abilityUpgrade->abilityImg = LoadTexture(stringBuff, m_renderer);
        abilityUpgrade->level = *m_upgradeManagerLevels[i];
        abilityUpgrade->frameRect = m_frameRectModel;
        abilityUpgrade->imgRect = m_imgRectModel;
        abilityUpgrade->frameRect.x = m_coor.x + (i % 3) * (m_frameRectModel.w + m_spacing);
        abilityUpgrade->frameRect.y = m_coor.y + (i / 3) * (m_frameRectModel.h + m_spacing);
        abilityUpgrade->imgRect.x = abilityUpgrade->frameRect.x + 3 + (coorBuff.x - abilityUpgrade->imgRect.w) / 2;
        abilityUpgrade->imgRect.y = abilityUpgrade->frameRect.y + 3 + (coorBuff.y - abilityUpgrade->imgRect.h) / 2;

        for(int j = 0; j < m_numberOfPrices; j++)
        {
            stream >> intBuff;
            abilityUpgrade->prices.push_back(intBuff);
        }

        stream >> abilityUpgrade->name >> abilityUpgrade->textCoor.x >> abilityUpgrade->textCoor.y;

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
    if((*m_mouseIsPressed))
    {
        for(int i = 0; i < m_shopArticles.size(); i++)
        {
            if(checkForMouseCollision(*m_mouseX, *m_mouseY, m_shopArticles[i]->frameRect) && m_shopArticles[i]->level < 8 && m_shopArticles[i]->prices[m_shopArticles[i]->level] <= *m_money)
            {
                *m_money -= m_shopArticles[i]->prices[m_shopArticles[i]->level];
                m_shopArticles[i]->level++;
                *m_upgradeManagerLevels[i] = m_shopArticles[i]->level;
            }
        }
        if(checkForMouseCollision(*m_mouseX, *m_mouseY, m_backButton))
        {
            (*m_quitScene) = true;
            (*m_gameState) = MENU;
        }
    }
}

void Shop::draw()
{
    SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, NULL);
    SDL_RenderCopy(m_renderer, m_backButtonTexture, NULL, &m_backButton);

    for(int i = 0; i < m_shopArticles.size(); i++)
    {
        SDL_RenderCopy(m_renderer, m_shopArticles[i]->abilityImg, NULL, &(m_shopArticles[i]->imgRect));
        coordinates coorBuff;
        coorBuff.x = m_shopArticles[i]->frameRect.x + m_shopArticles[i]->frameRect.w;
        coorBuff.y = m_shopArticles[i]->frameRect.y + m_shopArticles[i]->frameRect.h + 30;

        string stringBuff;

        if(m_shopArticles[i]->level != 8)
        {
            stringBuff = to_string(m_shopArticles[i]->prices[m_shopArticles[i]->level]) + " $";
        }
        else
        {
            stringBuff = "MAX LEVEL";
        }
        write(stringBuff, coorBuff, m_renderer, m_FONT_SIZE);
        write(m_shopArticles[i]->name, m_shopArticles[i]->textCoor, m_renderer, 24);
        SDL_RenderCopy(m_renderer, m_upgradeFrameTexture[m_shopArticles[i]->level], NULL, &(m_shopArticles[i]->frameRect));
    }

    string stringBuff = s_moneyText + to_string(*m_money);
    write(stringBuff, m_moneyTextCoor, m_renderer, m_FONT_SIZE);

    SDL_RenderPresent(m_renderer);
}
