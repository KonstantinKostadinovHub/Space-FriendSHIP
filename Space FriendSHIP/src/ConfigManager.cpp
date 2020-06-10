#include "ConfigManager.h"

ConfigManager::ConfigManager()
{
    //ctor
}

ConfigManager::~ConfigManager()
{
    //dtor
}

void ConfigManager::init(string configFile, SDL_Renderer* renderer)
{
    m_rock = new Enemy;
    m_shooter_default = new Shooter;
    m_shooter_sniper = new Shooter;
    m_shooter_tank = new Shooter;
    m_shooter_smg = new Shooter;
    m_zigzag = new ZigZag;
    m_player_enemy = new PlayerEnemy;

    m_bullet_deafult = new Projectile;
    m_bullet_sniper = new Projectile;
    m_bullet_tank = new Projectile;
    m_bullet_smg = new Projectile;
    m_bullet_zigzag = new Projectile;
    m_bullet_player = new Projectile;

    m_healthBooster = new Artefact;
    m_speedBooster = new Artefact;
    m_Stopper = new Artefact;
    m_Reverser = new Artefact;
    m_Coin = new Artefact;
    m_Shield = new Artefact;

    m_configFile = "config\\" + configFile;

    fstream stream;
    string tmp, buff;

    stream.open(m_configFile.c_str());
    stream >> tmp >> buff;
    m_rock -> load(buff, renderer);

    stream >> tmp >> buff;
    m_shooter_default -> load(buff, renderer);

    stream >> tmp >> buff;
    m_shooter_sniper -> load(buff, renderer);

    stream >> tmp >> buff;
    m_shooter_tank -> load(buff, renderer);

    stream >> tmp >> buff;
    m_shooter_smg -> load(buff, renderer);

    stream >> tmp >> buff;
    m_zigzag -> load(buff, renderer);

    stream >> tmp >> buff;
    m_player_enemy -> load(buff, renderer);

    stream >> tmp >> buff;
    m_bullet_deafult -> load(buff, renderer);

    stream >> tmp >> buff;
    m_bullet_sniper -> load(buff, renderer);

    stream >> tmp >> buff;
    m_bullet_tank -> load(buff, renderer);

    stream >> tmp >> buff;
    m_bullet_smg -> load(buff, renderer);

    stream >> tmp >> buff;
    m_bullet_zigzag -> load(buff, renderer);

    stream >> tmp >> buff;
    m_bullet_player -> load(buff, renderer);

    stream >> tmp >> buff;
    m_healthBooster -> load(buff, renderer);

    stream >> tmp >> buff;
    m_speedBooster -> load(buff, renderer);

    stream >> tmp >> buff;
    m_Stopper -> load(buff, renderer);

    stream >> tmp >> buff;
    m_Reverser -> load(buff, renderer);

    stream >> tmp >> buff;
    m_Coin -> load(buff, renderer);

    stream >> tmp >> buff;
    m_Shield -> load(buff, renderer);

    stream.close();
}
