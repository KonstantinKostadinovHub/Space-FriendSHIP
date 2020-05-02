#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <SDL2/SDL.h>

#include "Enemy.h"
#include "Projectile.h"
#include "Artefact.h"

#include "Rock.h"
#include "Shooter.h"
#include "ZigZag.h"
#include "PlayerEnemy.h"

#include "Bullet.h"

class ConfigManager
{
public:
    ConfigManager();
    virtual ~ConfigManager();

    string m_configFile;

    Enemy* m_rock;
    Enemy* m_shooter_default;
    Enemy* m_shooter_sniper;
    Enemy* m_shooter_tank;
    Enemy* m_shooter_smg;
    Enemy* m_zigzag;
    Enemy* m_player_enemy;

    Projectile* m_bullet_deafult;
    Projectile* m_bullet_sniper;
    Projectile* m_bullet_tank;
    Projectile* m_bullet_smg;
    Projectile* m_bullet_zigzag;
    Projectile* m_bullet_player;

    Artefact* m_healthBooster;
    Artefact* m_speedBooster;
    Artefact* m_Stopper;
    Artefact* m_Reverser;
    Artefact* m_Coin;
    Artefact* m_Shield;

    void init(string configFile, SDL_Renderer* renderer);
    void initObject(string configFile);
protected:

private:
};

#endif // CONFIGMANAGER_H
