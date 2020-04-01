#ifndef UPGRADEMANAGER_H
#define UPGRADEMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class UpgradeManager
{
public:
    vector<int> m_healthUpgrades;
    vector<int> m_bulletDamageUpgrades;
    vector<int> m_bulletSpeedUpgrades;
    vector<int> m_coinsMultiplierUpgrades;
    vector<int> m_dashUpgrades;
    vector<int> m_collisionDamageUpgrades;
    vector<int> m_healthBoosterUpgrades;
    vector<int> m_shieldBoosterDurationUpgrades;

    int m_CurrentLevelHealthUpgrade = 0;
    int m_CurrentLevelBulletDamageUpgrade = 0;
    int m_CurrentLevelBulletSpeedUpgrade = 0;
    int m_CurrentLevelCoinsMultiplierUpgrade = 0;
    int m_CurrentLevelDashUpgrade = 0;
    int m_CurrentLevelCollisionDamageUpgrade = 0;
    int m_CurrentLevelHealthBoosterUpgrade = 0;
    int m_CurrentLevelShieldBoosterDurationUpgrade = 0;

    int m_CurrentHealthUpgrade;
    int m_CurrentBulletDamageUpgrade;
    int m_CurrentBulletSpeedUpgrade;
    int m_CurrentCoinsMultiplierUpgrade;
    int m_CurrentDashUpgrade;
    int m_CurrentCollisionDamageUpgrade;
    int m_CurrentHealthBoosterUpgrade;
    int m_CurrentShieldBoosterDurationUpgrade;

    string m_configFile;

    void init(string configFile);
    void loadManager();

    UpgradeManager();
    virtual ~UpgradeManager();
protected:

private:
};

#endif // UPGRADEMANAGER_H
