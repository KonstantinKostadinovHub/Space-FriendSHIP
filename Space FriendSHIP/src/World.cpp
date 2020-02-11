#include "World.h"

World::World()
{
    //ctor
}

World::~World()
{
    //dtor
}

void World::init(string configFile)
{
        m_configFile = "config\\" + configFile;
        fstream stream;
        stream.open(m_configFile.c_str());
        stream >> m_SCREEN_WIDTH >> m_SCREEN_HEIGHT >> m_backgroundImg;
        stream.close();

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

void World::addEnemy(string configFile, int x, int y)
{
    if(configFile == "rock.txt")
    {
        Enemy* rock = new Rock();
        rock->init(configFile, x, y);
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

void World::cleaner()
{
    for(vector<Player*>::iterator it = m_players.begin(); it != m_players.end(); it++){
        // Чакам да се добавя health на играчът
    }
    for(vector<Enemy*>::iterator it = m_enemies.begin(); it != m_enemies.end(); it++){
        if((*it)->m_health <= 0)
        {
            cout << "dead";
            m_enemies.erase(it);
            it--;
        }
    }
    for(vector<Projectile*>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); it++){
        // проверка дали артефактът е взет
    }
    for(vector<Artefact*>::iterator it = m_artefacts.begin(); it != m_artefacts.end(); it++){
        // проверка дали артефактът е взет
    }
}
