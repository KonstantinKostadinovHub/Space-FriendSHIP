#include "World.h"

World::World()
{
    m_dropper = new Dropper;
    m_spawnManager = new Spawner;
    m_ScreenR.x = 300; //m_SCREEN_WIDTH/2-700;
    m_ScreenR.y = 100;//m_SCREEN_HEIGHT/2-700;
    m_ScreenR.w = 700;
    m_ScreenR.h = 700;
    m_ScreenMenu.x = 0;
    m_ScreenMenu.y = 0;
    m_ScreenMenu.w = m_SCREEN_WIDTH;
    m_ScreenMenu.h = m_SCREEN_HEIGHT;
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
    stream >> tmp >> m_spawnCooldown;
    stream >> tmp >> m_dropCooldown;
    stream.close();

    m_spawnManager -> init("spawner.txt");
    m_dropper -> init("dropper.txt");

    m_startDropCooldown = time(NULL);
    m_startSpawnCooldown = time(NULL);

    SDL_Init(SDL_INIT_EVERYTHING);

    //addPlayer(world.m_main_renderer, "player1.txt");


    m_main_window = SDL_CreateWindow("Space FriendSHIP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, 0);
    m_main_renderer = SDL_CreateRenderer(m_main_window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface* loadingSurface = SDL_LoadBMP("img\\background.bmp");
    m_backgroundTexture = SDL_CreateTextureFromSurface(m_main_renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
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
        //drop();
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

    //collisionDamage();
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
        player -> init(renderer, configFile);
        m_players.push_back(player);

    }
    else if(configFile == "player2.txt")
    {
        Player* player= new Player();
        player -> init(renderer, configFile);
        m_players.push_back(player);
    }
}

void World::collisionDamage(){
    for(int i = 0; i < m_players.size(); i++)
        {
            for(int j = 0; j < m_enemies.size(); j++){
                if(checkForCollisionBetweenObjects(m_players[i] -> m_objectRect, m_enemies[j] -> m_objectRect)){
                    m_players[i] -> m_health -= m_enemies[j] -> m_collisonDamage;
                }
            }
            for(int k = 0; k < m_projectiles.size(); k++){
                if(checkForCollisionBetweenObjects(m_players[i] -> m_objectRect, m_projectiles[k]->m_objectRect)==true){
                    m_players[i] -> m_health -= m_projectiles[k] -> m_collisonDamage;
                    m_projectiles[k] -> m_health = 0;
                }
            }
        }

    for(int m = 0; m < m_enemies.size(); m++){
        for(int n = 0; n < m_projectiles.size(); n++){
            if(checkForCollisionBetweenObjects(m_enemies[m] -> m_objectRect, m_projectiles[n] -> m_objectRect)==true){
                m_enemies[m] -> m_health -= m_projectiles[n] -> m_collisonDamage;
                m_projectiles[n] -> m_health=0;

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

bool World::checkForCollisionBetweenObjects(SDL_Rect rect1, SDL_Rect rect2)
{
    int minX = min(rect1.x, rect2.x);
    int maxX = max(rect1.x + rect1.w, rect2.x + rect2.w);

    int minY = min(rect1.y, rect2.y);
    int maxY = max(rect1.y + rect1.h, rect2.y + rect2.h);

    if ((maxX - minX < rect1.w + rect2.w) && (maxY - minY < rect1.h + rect2.h))
    {
        return true;
    }
    else
    {
        return false;
    }
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
    SDL_RenderCopy(m_main_renderer, m_EndTx, NULL, &m_ScreenR);
    SDL_FreeSurface(loadingEndGame);
    SDL_RenderPresent(m_main_renderer);
}

void World::menu()
{
    SDL_Texture* m_MenuTx;
    SDL_Surface* loadingMenu = SDL_LoadBMP(m_MenuImg.c_str());
    m_MenuTx = SDL_CreateTextureFromSurface(m_main_renderer, loadingMenu);
    SDL_RenderCopy(m_main_renderer, m_MenuTx, NULL, NULL);
    SDL_FreeSurface(loadingMenu);
    SDL_RenderPresent(m_main_renderer);

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_DOWN])
    {
        m_MenuImg = "img\\MENU_unfinished3.bmp";
    }
    else if(state[SDL_SCANCODE_UP])
    {
        m_MenuImg = "img\\MENU_unfinished2.bmp";

    }
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
        HealthBooster* Hboost = new HealthBooster();
        Hboost -> init(configFile, coor, direction);
        m_artefacts.push_back(Hboost);
    }
    if(configFile == "speedbooster.txt")
    {
        SpeedBooster* Sboost = new SpeedBooster();
        Sboost -> init(configFile, coor, direction);
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
        if(m_players[i] -> m_health == 0)
        {
            break;
            endgame = true;
        }
    }
    for(int i = 0; i < m_enemies.size(); i++)
    {
        if(m_enemies[i] -> m_health <= 0 || checkIfOffBounds(m_enemies[i] -> m_objectRect))
        {
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
        if(checkIfOffBounds(m_artefacts[i] -> m_objectRect))
        {
            m_artefacts.erase(m_artefacts.begin() + i);
            i--;
        }
    }
}
