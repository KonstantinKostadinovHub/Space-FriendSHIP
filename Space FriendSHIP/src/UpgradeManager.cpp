#include "UpgradeManager.h"

UpgradeManager::UpgradeManager()
{
    //ctor
}

UpgradeManager::~UpgradeManager()
{
    //dtor
}

void UpgradeManager::init(string configFile)
{
    m_configFile = "config\\" + configFile;
    fstream stream;
    string tmp;

    int buff;

    stream.open(m_configFile.c_str());
    stream >> tmp >> buff;
    stream >> tmp;
    for(int i = 0; i < buff ; i++)
    {
        int pushBackBuff;
        stream >> pushBackBuff;
        m_healthUpgrades.push_back(pushBackBuff);
    }
    stream >> tmp >> buff;
    stream >> tmp;
    for(int i = 0; i < buff ; i++)
    {
        int pushBackBuff;
        stream >> pushBackBuff;
        m_bulletDamageUpgrades.push_back(pushBackBuff);
    }
    stream >> tmp >> buff;
    stream >> tmp;
    for(int i = 0; i < buff ; i++)
    {
        int pushBackBuff;
        stream >> pushBackBuff;
        m_bulletSpeedUpgrades.push_back(pushBackBuff);
    }
    stream >> tmp >> buff;
    stream >> tmp;
    for(int i = 0; i < buff ; i++)
    {
        int pushBackBuff;
        stream >> pushBackBuff;
        m_coinsMultiplierUpgrades.push_back(pushBackBuff);
    }
    stream >> tmp >> buff;
    stream >> tmp;
    for(int i = 0; i < buff ; i++)
    {
        int pushBackBuff;
        stream >> pushBackBuff;
        m_dashUpgrades.push_back(pushBackBuff);
    }
    stream >> tmp >> buff;
    stream >> tmp;
    for(int i = 0; i < buff ; i++)
    {
        int pushBackBuff;
        stream >> pushBackBuff;
        m_collisionDamageUpgrades.push_back(pushBackBuff);
    }
    stream >> tmp >> buff;
    stream >> tmp;
    for(int i = 0; i < buff ; i++)
    {
        int pushBackBuff;
        stream >> pushBackBuff;
        m_healthBoosterUpgrades.push_back(pushBackBuff);
    }
    stream >> tmp >> buff;
    stream >> tmp;
    for(int i = 0; i < buff ; i++)
    {
        int pushBackBuff;
        stream >> pushBackBuff;
        m_shieldBoosterDurationUpgrades.push_back(pushBackBuff);
    }
    stream.close();
}

void UpgradeManager::loadManager()
{
    m_CurrentHealthUpgrade = m_healthUpgrades[m_CurrentLevelHealthUpgrade];
    m_CurrentBulletDamageUpgrade = m_bulletDamageUpgrades[m_CurrentLevelBulletDamageUpgrade];
    m_CurrentBulletSpeedUpgrade = m_bulletSpeedUpgrades[m_CurrentLevelBulletSpeedUpgrade];
    m_CurrentCoinsMultiplierUpgrade = m_coinsMultiplierUpgrades[m_CurrentLevelCoinsMultiplierUpgrade];
    m_CurrentDashUpgrade = m_dashUpgrades[m_CurrentLevelDashUpgrade];
    m_CurrentCollisionDamageUpgrade = m_collisionDamageUpgrades[m_CurrentLevelCollisionDamageUpgrade];
    m_CurrentHealthBoosterUpgrade = m_healthBoosterUpgrades[m_CurrentLevelHealthBoosterUpgrade];
    m_CurrentShieldBoosterDurationUpgrade = m_shieldBoosterDurationUpgrades[m_CurrentLevelShieldBoosterDurationUpgrade];
}
