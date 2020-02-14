#include "World.h"

World::World()
{
    m_spawnManager = new Spawner;
}

World::~World()
{
    //dtor
}

void World::init(string configFile)
{
        srand(time(NULL));
        m_startSpawnCooldown = time(NULL);
        m_configFile = "config\\" + configFile;
        fstream stream;
        stream.open(m_configFile.c_str());
        stream >> m_SCREEN_WIDTH >> m_SCREEN_HEIGHT >> m_backgroundImg >> m_spawnCooldown;
        stream.close();
        m_spawnManager->init("spawner.txt");

        SDL_Init(SDL_INIT_EVERYTHING);

        m_main_window = SDL_CreateWindow("Space FriendSHIP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, 0);
        m_main_renderer = SDL_CreateRenderer(m_main_window, -1, SDL_RENDERER_ACCELERATED);

        string path = "img\\" + m_backgroundImg;
        SDL_Surface* loadingSurface= SDL_LoadBMP(path.c_str());
        m_backgroundTexture = SDL_CreateTextureFromSurface(m_main_renderer, loadingSurface);
        SDL_FreeSurface(loadingSurface);
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

    for(vector<Player*>::iterator it = m_players.begin(); it != m_players.end(); it++){
        (*it)->update();
    }
    for(vector<Enemy*>::iterator it = m_enemies.begin(); it != m_enemies.end(); it++){
        (*it)->update();
    }
    for(vector<Projectile*>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); it++){
        (*it)->update();
    }
    for(vector<Artefact*>::iterator it = m_artefacts.begin(); it != m_artefacts.end(); it++){
        (*it)->update();
    }

    cleaner();
}

void World::draw()
{
    SDL_RenderCopy(m_main_renderer, m_backgroundTexture, NULL, NULL);

    for(vector<Player*>::iterator it = m_players.begin(); it != m_players.end(); it++){
        (*it)->draw(m_main_renderer);
    }
    for(vector<Enemy*>::iterator it = m_enemies.begin(); it != m_enemies.end(); it++){
        (*it)->draw(m_main_renderer);
    }
    for(vector<Projectile*>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); it++){
        (*it)->draw(m_main_renderer);
    }
    for(vector<Artefact*>::iterator it = m_artefacts.begin(); it != m_artefacts.end(); it++){
        (*it)->draw(m_main_renderer);
    }

    SDL_RenderPresent(m_main_renderer);
}

void World::destroy()
{
        SDL_DestroyRenderer(m_main_renderer);
        SDL_DestroyWindow(m_main_window);
}

void World::addEnemy(string configFile, int x, int y, float directionX, float directionY)
{
    if(configFile == "rock.txt")
    {
        Enemy* rock = new Rock();
        cout << x << ", " << y << ", " << directionX << ", " << directionY << endl;
        rock->init(configFile, x, y, directionX, directionY);
        m_enemies.push_back(rock);
    }
}

bool World::checkForCollisionBetweenObjects(SDL_Rect rect1, SDL_Rect rect2)
{
    int minX = min(rect1.x, rect2.x);
    int maxX = max(rect1.x + rect1.w, rect2.x + rect2.w);

    int minY = min(rect1.y, rect2.y);
    int maxY = max(rect1.y + rect1.h, rect2.y + rect2.h);

    if ((maxX - minX < rect1.w + rect2.w) && (maxY - minY < rect1.h + rect2.h)) {
        return true;
    }
    else
    {
        return false;
    }
}

bool World::checkIfOffBounds(SDL_Rect rect)
{
    if (rect.x + rect.w > m_SCREEN_WIDTH) return true;
    if (rect.x < 0) return true;
    if (rect.y + rect.h > m_SCREEN_HEIGHT) return true;
    if (rect.y < 0) return true;
    return false;
}

void World::cleaner()
{
    for(vector<Player*>::iterator it = m_players.begin(); it != m_players.end(); it++){
        // Чакам да се добавя health на играчът
    }
    for(int i = 0; i < m_enemies.size(); i++){
        if(m_enemies[i]->m_health <= 0 || checkIfOffBounds(m_enemies[i]->m_objectRect))
        {
            cout << "DEAD" << endl;
            m_enemies.erase(m_enemies.begin() + i);
            i--;
        }
    }
    for(vector<Projectile*>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); it++){
        // проверка дали артефактът е взет
    }
    for(vector<Artefact*>::iterator it = m_artefacts.begin(); it != m_artefacts.end(); it++){
        // проверка дали артефактът е взет
    }
}

void World::spawn()
{
    m_spawnManager->spawn(m_SCREEN_WIDTH, m_SCREEN_HEIGHT);
    addEnemy(m_spawnManager->m_type, m_spawnManager->m_x, m_spawnManager->m_y, m_spawnManager->m_directionX, m_spawnManager->m_directionY);
}
