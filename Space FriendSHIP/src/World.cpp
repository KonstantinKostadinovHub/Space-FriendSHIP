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
        m_configFile = configFile;
        fstream stream;
        stream.open(m_configFile.c_str());
        stream >> m_SCREEN_WIDTH >> m_SCREEN_HEIGHT >> m_backgroundImg;

        SDL_Init(SDL_INIT_EVERYTHING);

        m_main_window = SDL_CreateWindow("Space FriendSHIP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_SCREEN_WIDTH, m_SCREEN_HEIGHT, 0);
        m_main_renderer = SDL_CreateRenderer(m_main_window, -1, SDL_RENDERER_ACCELERATED);

        SDL_Surface* loadingSurface= SDL_LoadBMP("img\\background.bmp");
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
