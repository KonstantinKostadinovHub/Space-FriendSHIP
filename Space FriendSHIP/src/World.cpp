#include "World.h"

World::World()
{
    m_dropper = new Dropper;
    m_spawnManager = new Spawner;
    m_upgradeManager = new UpgradeManager;
    m_configManager = new ConfigManager;
    m_shop = new Shop;
    m_soundManager = new SoundManager;
}

World::~World()
{

}

void World::init(string configFile)
{
    srand(time(NULL));

    m_configFile = "config\\" + configFile;
    fstream stream;

    stream.open(m_configFile.c_str());
    stream >> tmp >> m_SCREEN_WIDTH >> m_SCREEN_HEIGHT;
    stream >> tmp >> m_backgroundImg;
    stream >> tmp >> m_endScreenImg;
    stream >> tmp >> m_menuImg1;
    stream >> tmp >> m_menuImg2;
    stream >> tmp >> m_menuImg3;
    stream >> tmp >> m_spawnCooldown;
    stream >> tmp >> m_dropCooldown;
    stream >> tmp >> m_enemiesPerSpawn;
    stream.close();

    m_startDropCooldown = time(NULL);
    m_startSpawnCooldown = time(NULL);

    SDL_Init(SDL_INIT_EVERYTHING);

    m_main_window = SDL_CreateWindow("Space FriendSHIP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, 0);
    m_main_renderer = SDL_CreateRenderer(m_main_window, -1, SDL_RENDERER_ACCELERATED);

    m_spawnManager -> init("spawner.txt");
    m_dropper -> init("dropper.txt");
    m_upgradeManager -> init("upgrade_manager.txt");
    loadProgress();
    m_configManager -> init("config_manager.txt", m_main_renderer);
    m_shop -> init("shop.txt", m_configManager, m_main_renderer, &mouseX, &mouseY, &mouseIsPressed, &m_wallet, m_upgradeManager);
    m_soundManager -> init("SoundManager.txt");

    SDL_Surface* loadingSurface = SDL_LoadBMP("img\\background.bmp");
    m_backgroundTexture = SDL_CreateTextureFromSurface(m_main_renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);

    m_ScreenR.x = 0;
    m_ScreenR.y = 0;
    m_ScreenR.w = m_SCREEN_WIDTH;
    m_ScreenR.h = m_SCREEN_HEIGHT;
    m_ScreenMenu.x = 0;
    m_ScreenMenu.y = 0;
    m_ScreenMenu.w = m_SCREEN_WIDTH;
    m_ScreenMenu.h = m_SCREEN_HEIGHT;

    m_endScreenImg = "img\\" + m_endScreenImg;
    m_menuImg1 = "img\\" + m_menuImg1;
    m_menuImg2 = "img\\" + m_menuImg2;
    m_menuImg3 = "img\\" + m_menuImg3;

    m_menuImg = m_menuImg1;

    SDL_SetWindowFullscreen(m_main_window, SDL_WINDOW_FULLSCREEN);

    m_soundManager -> play_sound("General.mp3");
}

void World::update()
{
    if(!m_spawn)
    {
        m_spawn = true;
        m_startSpawnCooldown = time(NULL);
        for(int i = 0; i < m_enemiesPerSpawn; i++)
        {
            spawn();
        }
    }
    else if(m_startSpawnCooldown + m_spawnCooldown < time(NULL))
    {
        m_spawn = false;
    }

    if(m_drop)
    {
        m_drop = false;
        m_startDropCooldown = time(NULL);
        drop();
    }
    else if(m_startDropCooldown + m_dropCooldown < time(NULL))
    {
        m_drop = true;
    }
    for(int i = 0; i < m_players.size(); i++)
    {
        if(m_players[i]->inDash)
        {
            string buff = "dash.txt";
            addAnimation(buff, m_players[i]->m_oldCoor, m_main_renderer, m_players[i]->m_rotationAngle, &(m_players[i]->m_center));
            m_players[i] -> inDash = false;
            m_soundManager -> play_sound("Dash.mp3");
        }
    }
    for(vector <Player*> :: iterator it = m_players.begin(); it != m_players.end(); it++)
    {
        (*it) -> update();
    }
    for(vector <Enemy*> :: iterator it = m_enemies.begin(); it != m_enemies.end(); it++)
    {
        (*it) -> update();
    }
    for(vector <Projectile*> :: iterator it = m_projectiles.begin(); it != m_projectiles.end(); it++)
    {
        (*it) -> update();
    }
    for(vector <Artefact*> :: iterator it = m_artefacts.begin(); it != m_artefacts.end(); it++)
    {
        (*it) -> update();
    }
    for(vector <Animation*> :: iterator it = m_animations.begin(); it != m_animations.end(); it++)
    {
        (*it) -> update();
    }

    shootProjectiles();

    collisionDamage();
}

void World::draw()
{
    SDL_RenderCopy(m_main_renderer, m_backgroundTexture, NULL, NULL);

    for(vector <Enemy*> :: iterator it = m_enemies.begin(); it != m_enemies.end(); it++)
    {
        (*it) -> draw(m_main_renderer);
    }
    for(vector <Projectile*> :: iterator it = m_projectiles.begin(); it != m_projectiles.end(); it++)
    {
        (*it) -> draw(m_main_renderer);
    }
    for(vector <Artefact*> :: iterator it = m_artefacts.begin(); it != m_artefacts.end(); it++)
    {
        (*it) -> draw(m_main_renderer);
    }
    for(vector <Player*> :: iterator it = m_players.begin(); it != m_players.end(); it++)
    {
        (*it) -> draw(m_main_renderer);
    }
    for(vector <Animation*> :: iterator it = m_animations.begin(); it != m_animations.end(); it++)
    {
        (*it) -> draw(m_main_renderer);
    }

    SDL_RenderPresent(m_main_renderer);
}

void World::destroy()
{
    SDL_DestroyRenderer(m_main_renderer);
    SDL_DestroyWindow(m_main_window);
}

void World::addPlayer(SDL_Renderer* renderer, string configFile)
{
    if(configFile == "player1.txt")
    {
        Player* player = new Player();
        player -> init(renderer, configFile, m_upgradeManager);
        m_players.push_back(player);

    }
    else if(configFile == "player2.txt")
    {
        Player* player= new Player();
        player -> init(renderer, configFile, m_upgradeManager);
        m_players.push_back(player);
    }
}

void World::addPlayerAI(SDL_Renderer* renderer, string configFile)
{
    Player_AI* playerAI = new Player_AI();
    playerAI -> init( configFile,renderer);
    m_players.push_back(playerAI);
}

void World::collisionDamage()
{
    for(int i = 0; i < m_players.size(); i++)
    {
        for(int j = 0; j < m_enemies.size(); j++)
        {
            if(checkForCollisionBetweenObjects(m_players[i]->m_objectRect, m_players[i]->m_rotationAngle, &m_players[i]->m_center,
                                               m_enemies[j]->m_objectRect, m_enemies[j]->m_rotationAngle, &m_enemies[j]->m_center))
            {
                m_players[i]->m_health -= m_enemies[j]->m_collisonDamage;
                m_enemies[j]->m_health -= m_players[i]->m_collisionDamage + m_upgradeManager->m_CurrentCollisionDamageUpgrade;
                addAnimation("explosion.txt",m_enemies[j]->m_coor,m_main_renderer,0);
                m_soundManager -> play_sound("Explosion.mp3");

            }
        }
        for(int k = 0; k < m_projectiles.size(); k++)
        {
            if(checkForCollisionBetweenObjects(m_players[i]->m_objectRect, m_players[i]->m_rotationAngle,&m_players[i]->m_center,
                                               m_projectiles[k]->m_objectRect,m_projectiles[k]->m_rotationAngle, NULL))
            {
                m_players[i]->m_health -= m_projectiles[k]->m_collisonDamage;
                m_projectiles[k]->m_health = 0;
                addAnimation("explosion.txt",m_projectiles[k]->m_coor,m_main_renderer,0);
                m_soundManager -> play_sound("Explosion.mp3");
            }
        }
        for(int p = 0; p < m_artefacts.size(); p++)
        {
            if(checkForCollisionBetweenObjects(m_players[i] -> m_objectRect, m_players[i]->m_rotationAngle, &m_players[i] ->m_center,
                                               m_artefacts[p]->m_objectRect, 0, NULL))
            {
                if(m_artefacts[p] -> m_configFile == "healthbooster.txt")
                {
                    m_players[i] -> m_health += m_artefacts[p] -> m_actionEffect;
                    m_artefacts[p] -> m_health = 0;
                    m_soundManager -> play_sound("Healing.mp3");
                }
                if(m_artefacts[p] -> m_configFile == "speedbooster.txt")
                {
                    m_players[i] -> m_speed += m_artefacts[p] -> m_actionEffect;
                    m_artefacts[p] -> m_health = 0;
                    m_soundManager -> play_sound("Dash.mp3");
                }
                if(m_artefacts[p] -> m_configFile == "stopper.txt")
                {
                    m_players[i] -> m_speed = m_artefacts[p] -> m_actionEffect;
                    m_artefacts[p] -> m_health = 0;
                    m_soundManager -> play_sound("Stop.mp3");
                }
                if(m_artefacts[p] -> m_configFile == "reverser.txt")
                {
                    m_players[i] -> m_speed = m_artefacts[p] -> m_actionEffect;
                    m_artefacts[p] -> m_health = 0;
                    m_soundManager -> play_sound("Reverse.mp3");
                }
            }
        }
    }

    for(int m = 0; m < m_enemies.size(); m++)
    {
        for(int n = 0; n < m_projectiles.size(); n++)
        {
            if(checkForCollisionBetweenObjects(m_enemies[m]->m_objectRect, m_enemies[m]->m_rotationAngle, &m_enemies[m]->m_center,
                                               m_projectiles[n]->m_objectRect, m_projectiles[n]->m_rotationAngle, NULL))
            {
                m_enemies[m]->m_health -= m_projectiles[n]->m_collisonDamage;
                m_projectiles[n]->m_health = 0;
                addAnimation("explosion.txt",m_projectiles[n]->m_coor,m_main_renderer,0);
                m_soundManager -> play_sound("Explosion.mp3");
            }
        }
    }
}

void World::addEnemy(string configFile, coordinates coor, float rotation)
{
    Enemy* model;
    Enemy* enemy;

    if(configFile == "rock")
    {
        model = m_configManager -> m_rock;
        enemy = new Enemy;
    }
    else if (configFile == "shooter_default")
    {
        model = m_configManager -> m_shooter_default;
        enemy = new Shooter;
    }
    else if (configFile == "shooter_sniper")
    {
        model = m_configManager -> m_shooter_sniper;
        enemy = new Shooter;
    }
    else if(configFile == "shooter_tank")
    {
        model = m_configManager -> m_shooter_tank;
        enemy = new Shooter;
    }
    else if(configFile == "shooter_smg")
    {
        model = m_configManager -> m_shooter_smg;
        enemy = new Shooter;
    }
    else if (configFile == "zigzag")
    {
        model = m_configManager -> m_zigzag;
        enemy = new ZigZag;
    }
    enemy -> init(configFile, coor, rotation, model);
    m_enemies.push_back(enemy);
}

void World::addBullet(string configFile, coordinates coor, float rotation)
{
    Projectile* model;

    if(configFile == "bullet_default.txt")
    {
        model = m_configManager->m_bullet_deafult;
    }
    else if(configFile == "bullet_tank.txt")
    {
        model = m_configManager->m_bullet_tank;
    }
    else if(configFile == "bullet_sniper.txt")
    {
        model = m_configManager->m_bullet_sniper;
    }
    else if(configFile == "bullet_smg.txt")
    {
        model = m_configManager->m_bullet_smg;
    }
    else if(configFile == "bullet_zigzag.txt")
    {
        model = m_configManager->m_bullet_zigzag;
    }
    else if(configFile == "bullet_player.txt")
    {
        model = m_configManager->m_bullet_player;
    }

    Projectile* proj = new Bullet();
    proj -> init(configFile, coor, rotation, model);
    m_projectiles.push_back(proj);
}

void World::addArtefact(string configFile,coordinates coor, coordinates direction)
{
    Artefact* model;

    if(configFile == "healthbooster.txt")
    {
        model = m_configManager -> m_healthBooster;
    }
    else if(configFile == "speedbooster.txt")
    {
        model = m_configManager -> m_speedBooster;
    }
    else if(configFile == "stopper.txt")
    {
        model = m_configManager -> m_Stopper;
    }
    else if(configFile == "reverser.txt")
    {
        model = m_configManager -> m_Reverser;
    }

    Artefact* artefact = new Artefact();
    artefact -> init(configFile, coor, direction, model);
    m_artefacts.push_back(artefact);
}

void World::spawn()
{
    m_spawnManager -> spawn(m_SCREEN_WIDTH, m_SCREEN_HEIGHT);
    float angle = returnAngleByCoordinates(m_spawnManager -> m_direction);
    addEnemy(m_spawnManager -> m_type, m_spawnManager -> m_coor, angle);
}

void World::endgameScreen()
{
    SDL_Texture* m_EndTx;
    SDL_Surface* loadingEndGame = SDL_LoadBMP(m_endScreenImg.c_str());
    m_EndTx = SDL_CreateTextureFromSurface(m_main_renderer, loadingEndGame);
    SDL_RenderCopy(m_main_renderer, m_EndTx, &m_ScreenR, NULL);
    SDL_FreeSurface(loadingEndGame);
    SDL_RenderPresent(m_main_renderer);
}

void World::menu()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_RIGHT])
    {
        m_menuImg = m_menuImg3;
    }
    else if(state[SDL_SCANCODE_LEFT])
    {
        m_menuImg = m_menuImg2;
    }

    SDL_Texture* m_MenuTx;
    SDL_Surface* loadingMenu = SDL_LoadBMP(m_menuImg.c_str());
    m_MenuTx = SDL_CreateTextureFromSurface(m_main_renderer, loadingMenu);
    SDL_RenderCopy(m_main_renderer, m_MenuTx, NULL, NULL);
    SDL_FreeSurface(loadingMenu);
    SDL_RenderPresent(m_main_renderer);
}

void World::shootProjectiles()
{
    for(int i = 0; i < m_enemies.size(); i++)
    {
        for(int j = 0; j < m_enemies[i] -> m_guns.size(); j++)
        {
            if(!m_enemies[i] -> m_guns[j] -> m_cantShoot)
            {
                struct coordinates buff;
                buff.x = m_enemies[i] -> m_guns[j] -> m_objectRect.x;
                buff.y = m_enemies[i] -> m_guns[j] -> m_objectRect.y;
                addBullet(m_enemies[i] -> m_bulletName, buff, m_enemies[i] -> m_guns[j] -> m_rotationAngle);
            }
            for(vector <Animation*> :: iterator it = m_animations.begin(); it != m_animations.end(); it++)
            {
                (*it) -> update();
            }
        }
    }

    for(int i = 0; i < m_players.size(); i++)
    {
        for(int j = 0; j < m_players[i] -> m_guns.size(); j++)
        {
            if(!m_players[i] -> m_guns[j] -> m_cantShoot)
            {
                struct coordinates buff;
                buff.x = m_players[i] -> m_guns[j] -> m_objectRect.x;
                buff.y = m_players[i] -> m_guns[j] -> m_objectRect.y;
                addBullet(m_players[i] -> m_bulletName, buff, m_players[i] -> m_guns[j] -> m_rotationAngle);
                m_soundManager->play_sound("Shooting.mp3");
            }
        }
    }
}

void World::drop()
{
    m_dropper -> spawn(m_SCREEN_WIDTH, m_SCREEN_HEIGHT);
    addArtefact(m_dropper -> m_type, m_dropper -> m_coor, m_dropper -> m_direction);
}

void World::cleaner()
{
    for(int i = 0; i < m_players.size(); i++)
    {
        if(m_players[i] -> m_health <= 0)
        {
            endgame = true;
            m_players.erase(m_players.begin() + i);
            i--;
            break;
        }
    }
    for(int i = 0; i < m_enemies.size(); i++)
    {
        if(m_enemies[i] -> m_health <= 0 || checkIfOffBounds(m_enemies[i] -> m_objectRect, m_SCREEN_WIDTH, m_SCREEN_HEIGHT))
        {
            if(m_enemies[i] -> m_health <= 0)
            {
                AddPoints(m_enemies[i]);
            }

            if(m_enemies[i] -> m_health <= 0)
            {
                AddCoins(m_enemies[i]);
            }
            m_enemies.erase(m_enemies.begin() + i);
            i--;
        }
    }
    for(int i = 0; i < m_projectiles.size(); i++)
    {
        if(m_projectiles[i] -> m_health <= 0 ||checkIfOffBounds(m_projectiles[i] -> m_objectRect, m_SCREEN_WIDTH, m_SCREEN_HEIGHT))
        {
            m_projectiles.erase(m_projectiles.begin() + i);
            i--;
        }
    }
    for(int i = 0; i < m_artefacts.size(); i++)
    {
        if(checkIfOffBounds(m_artefacts[i] -> m_objectRect, m_SCREEN_WIDTH, m_SCREEN_HEIGHT) || m_artefacts[i]->m_health <= 0 )
        {
            m_artefacts.erase(m_artefacts.begin() + i);
            i--;
        }
    }
}

void World::saveProgress()
{
    SaveInFile("bulletDamageUpgrade.txt", "Level:", m_upgradeManager->m_CurrentLevelBulletDamageUpgrade);
    SaveInFile("bulletSpeedUpgrade.txt", "Level:", m_upgradeManager->m_CurrentLevelBulletSpeedUpgrade);
    SaveInFile("collisionUpgrade.txt", "Level:", m_upgradeManager->m_CurrentLevelCollisionDamageUpgrade);
    SaveInFile("dashUpgrade.txt", "Level:", m_upgradeManager->m_CurrentLevelDashUpgrade);
    SaveInFile("moneyUpgrade.txt", "Level:", m_upgradeManager->m_CurrentLevelCoinsMultiplierUpgrade);
    SaveInFile("healthUpgrade.txt", "Level:", m_upgradeManager->m_CurrentLevelHealthUpgrade);
    SaveInFile("healthBoosterUpgrade.txt", "Level:", m_upgradeManager->m_CurrentLevelHealthBoosterUpgrade);
    SaveInFile("shieldBoosterUpgrade.txt", "Level:", m_upgradeManager->m_CurrentLevelShieldBoosterDurationUpgrade);
    SaveInFile("wallet.txt", "Money_in_wallet:", m_wallet);
}

void World::loadProgress()
{
    m_upgradeManager->m_CurrentLevelBulletDamageUpgrade = LoadFromFile("bulletDamageUpgrade.txt");
    m_upgradeManager->m_CurrentLevelBulletSpeedUpgrade = LoadFromFile("bulletSpeedUpgrade.txt");
    m_upgradeManager->m_CurrentLevelCollisionDamageUpgrade = LoadFromFile("collisionUpgrade.txt");
    m_upgradeManager->m_CurrentLevelCoinsMultiplierUpgrade = LoadFromFile("moneyUpgrade.txt");
    m_upgradeManager->m_CurrentLevelDashUpgrade = LoadFromFile("dashUpgrade.txt");
    m_upgradeManager->m_CurrentLevelHealthUpgrade = LoadFromFile("healthUpgrade.txt");
    m_upgradeManager->m_CurrentLevelHealthBoosterUpgrade = LoadFromFile("healthBoosterUpgrade.txt");
    m_upgradeManager->m_CurrentLevelShieldBoosterDurationUpgrade = LoadFromFile("shieldBoosterUpgrade.txt");
    m_upgradeManager->loadManager();
    m_wallet = LoadFromFile("wallet.txt");
}

void World::AddPoints(Enemy* enemy)
{
    m_points += enemy -> m_pointsGiven;
}

void World::AddCoins(Enemy* enemy)
{
    m_coins += enemy -> m_pointsGiven + m_upgradeManager->m_CurrentCoinsMultiplierUpgrade;
}

void World::chooseGameMode()
{
    if(m_menuImg == m_menuImg2)
    {
        addPlayer (m_main_renderer, "player1.txt");
        addPlayerAI (m_main_renderer,"playerAI.txt");
    }
    else if(m_menuImg == m_menuImg3)
    {
        addPlayer (m_main_renderer, "player2.txt");
        addPlayer (m_main_renderer, "player1.txt");
    }
}

void World::shop()
{
    m_shop->update();
    m_shop->draw();
}

void World::addAnimation(string configFile, coordinates coor,SDL_Renderer* renderer,float rotation,SDL_Point* center)
{

    Animation* animation = new Animation;
    animation -> init(configFile, coor,renderer,rotation,center);
    m_animations.push_back(animation);
}

void World::initSession()
{
    m_startDropCooldown = time(NULL);
    m_startSpawnCooldown = time(NULL);
}

void World::destroySession()
{
    for(int i = 0; i < m_players.size(); i++)
    {
        m_players.erase(m_players.begin() + i);
        i--;
    }
    for(int i = 0; i < m_enemies.size(); i++)
    {
        m_enemies.erase(m_enemies.begin() + i);
        i--;
    }
    for(int i = 0; i < m_projectiles.size(); i++)
    {
        m_projectiles.erase(m_projectiles.begin() + i);
        i--;
    }
    for(int i = 0; i < m_artefacts.size(); i++)
    {
        m_artefacts.erase(m_artefacts.begin() + i);
        i--;
    }
}
