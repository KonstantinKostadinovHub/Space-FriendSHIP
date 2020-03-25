#include "World.h"

World::World()
{
    m_dropper = new Dropper;
    m_spawnManager = new Spawner;
    m_upgradeManager = new UpgradeManager;
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
    stream.close();

    m_spawnManager -> init("spawner.txt");
    m_dropper -> init("dropper.txt");
    m_upgradeManager -> init("upgrade_manager.txt");

    m_startDropCooldown = time(NULL);
    m_startSpawnCooldown = time(NULL);

    SDL_Init(SDL_INIT_EVERYTHING);

    m_main_window = SDL_CreateWindow("Space FriendSHIP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, 0);
    m_main_renderer = SDL_CreateRenderer(m_main_window, -1, SDL_RENDERER_ACCELERATED);

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

/*
    Player_AI* bot_AI = new Player_AI();
    bot_AI->init("PlayerAI.txt", m_main_renderer);
    m_players.push_back(bot_AI);
*/
}

void World::update()
{
    if(!m_spawn)
    {
        m_spawn = true;
        m_startSpawnCooldown = time(NULL);
        spawn();
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
            for(int j = 0; j < m_enemies.size(); j++){
                if(checkForCollisionBetweenObjects(m_players[i]->m_objectRect, m_players[i]->m_rotationAngle,
                                                   m_enemies[j]->m_objectRect, m_enemies[j]->m_rotationAngle)){
                    m_players[i]->m_health -= m_enemies[j]->m_collisonDamage;

                }
            }
            for(int k = 0; k < m_projectiles.size(); k++){
                if(checkForCollisionBetweenObjects(m_players[i]->m_objectRect, m_players[i]->m_rotationAngle,
                                                   m_projectiles[k]->m_objectRect,m_projectiles[k]->m_rotationAngle)==true){
                    m_players[i]->m_health -= m_projectiles[k]->m_collisonDamage;
                    m_projectiles[k]->m_health = 0;
                }
            }
            for(int p = 0; p < m_artefacts.size(); p++){
                if(checkForCollisionBetweenObjects(m_players[i] -> m_objectRect, m_players[i]->m_rotationAngle,
                                                   m_artefacts[p]->m_objectRect, 0)==true){
                    if(m_artefacts[p] -> m_type == "healthbooster"){
                        m_players[i] -> m_health += (m_artefacts[p] -> m_actionEffect) + m_upgradeManager->m_CurrentHealthBoosterUpgrade;
                        m_artefacts[p] -> m_health = 0;

                    }
                    if(m_artefacts[p] -> m_type == "speedbooster"){
                        m_players[i] -> m_speed += m_artefacts[p] -> m_actionEffect;
                        m_artefacts[p] -> m_health = 0;
                    }
                }
            }
        }

    for(int m = 0; m < m_enemies.size(); m++){
        for(int n = 0; n < m_projectiles.size(); n++){
            if(checkForCollisionBetweenObjects(m_enemies[m]->m_objectRect, m_enemies[m]->m_rotationAngle,
                                               m_projectiles[n]->m_objectRect, m_projectiles[n]->m_rotationAngle)==true){
                m_enemies[m]->m_health -= m_projectiles[n]->m_collisonDamage;
                m_projectiles[n]->m_health=0;

               }
        }
    }

}

void World::addEnemy(string configFile, coordinates coor, float rotation)
{
    if(configFile == "rock.txt")
    {
        Enemy* enemy = new Rock();
        enemy -> init(configFile, coor, rotation, m_main_renderer);
        m_enemies.push_back(enemy);
    }else if (configFile == "shooter_default.txt" || configFile == "shooter_sniper.txt" || configFile == "shooter_smg.txt" || configFile == "shooter_tank.txt")
    {
        Enemy* enemy = new Shooter();
        enemy -> init(configFile, coor, rotation, m_main_renderer);
        m_enemies.push_back(enemy);
    }else if (configFile == "zigzag.txt")
    {
        Enemy* enemy = new ZigZag();
        enemy -> init(configFile, coor, rotation, m_main_renderer);
        m_enemies.push_back(enemy);
    }
}

void World::addBullet(string configFile, coordinates coor, float rotation)
{
    if(configFile == "bullet_default.txt" || configFile == "bullet_sniper.txt" || configFile == "bullet_smg.txt" || configFile == "bullet_tank.txt")
    {
        Projectile* proj = new Bullet();
        proj -> init(configFile, coor, rotation, m_main_renderer);
        m_projectiles.push_back(proj);
    }
}

bool World::checkForCollisionBetweenObjects(SDL_Rect rect_no_rotation1, float angle1, SDL_Rect rect_no_rotation2, float angle2)
{
    bool colide = false;
    coordinates c1, c2;

    c1 = findCenter(rect_no_rotation1, angle1, NULL);
    c2 = findCenter(rect_no_rotation2, angle2, NULL);

    float a_2 = (c1.x - c2.x)*(c1.x - c2.x);
    float b_2 = (c1.y - c2.y)*(c1.y - c2.y);
    float c_2 = 6*6;

    return (a_2 + b_2 <= c_2);
}

bool World::checkIfOffBounds(SDL_Rect rect)
{
    if (rect.x + rect.w > m_SCREEN_WIDTH)
        return true;
    if (rect.x < 0)
        return true;
    if (rect.y + rect.h > m_SCREEN_HEIGHT)
        return true;
    if (rect.y < 0)
        return true;
    return false;
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
            if(!m_enemies[i] -> m_guns[j] -> m_cantShoot){
                struct coordinates buff;
                buff.x = m_enemies[i] -> m_guns[j] -> m_objectRect.x;
                buff.y = m_enemies[i] -> m_guns[j] -> m_objectRect.y;
                addBullet(m_enemies[i] -> m_bulletName, buff, m_enemies[i] -> m_guns[j] -> m_rotationAngle);
            }
        }
    }
}

void World::addArtefact(string configFile,coordinates coor, coordinates direction)
{
    if(configFile == "healthbooster.txt")
    {
        Artefact* Hboost = new Artefact();
        Hboost -> init(configFile, coor, direction,m_main_renderer);
        Hboost -> m_type = "healthbooster";
        m_artefacts.push_back(Hboost);

    }
    if(configFile == "speedbooster.txt")
    {
        Artefact* Sboost = new Artefact();
        Sboost -> init(configFile, coor, direction,m_main_renderer);
        Sboost -> m_type = "speedbooster";
        m_artefacts.push_back(Sboost);
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

            m_players.erase(m_players.begin() + i);
            i--;
            endgame = true;
            break;
        }
    }
    for(int i = 0; i < m_enemies.size(); i++)
    {
        if(m_enemies[i] -> m_health <= 0 || checkIfOffBounds(m_enemies[i] -> m_objectRect))
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
        if(m_projectiles[i] -> m_health <= 0 ||checkIfOffBounds(m_projectiles[i] -> m_objectRect))
        {
            m_projectiles.erase(m_projectiles.begin() + i);
            i--;
        }
    }
    for(int i = 0; i < m_artefacts.size(); i++)
        {
        if(checkIfOffBounds(m_artefacts[i] -> m_objectRect) || m_artefacts[i]->m_health <= 0 )
        {
            m_artefacts.erase(m_artefacts.begin() + i);
            i--;
        }
   }
}

void World::saveProgress()
{
    SaveInFile("wallet.txt", "Money_in_wallet:", m_wallet);
}

void World::loadProgress()
{
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

void World::chooseGameMode(){
    if(m_menuImg == m_menuImg2)
    {
        addPlayer (m_main_renderer, "player1.txt");
        addPlayerAI (m_main_renderer,"playerAI.txt");
    }else if(m_menuImg == m_menuImg3)
    {
        addPlayer (m_main_renderer, "player2.txt");
        addPlayer (m_main_renderer, "player1.txt");
    }
}
