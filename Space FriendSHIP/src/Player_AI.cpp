#include "Player_AI.h"
#include "World.h"

extern World world;

Player_AI::Player_AI()
{
    m_rotationAngle = .0;
    m_elapsed_shoot = chrono::high_resolution_clock::now();
    m_elapsed_engage = chrono::high_resolution_clock::now();
    m_shootingRate = 500ms;
    m_engagementRate = 5000ms;
    m_follow = false;
}

Player_AI::~Player_AI()
{
    //dtor
}

void Player_AI::init(string config, SDL_Renderer* renderer)
{
    m_health = 1000000;

    m_configFile = "config\\" + config;
    fstream stream;
    string tmp;
    stream.open(m_configFile.c_str());
    stream >> tmp >> m_objectRect.w >> m_objectRect.h;
    stream >> tmp >> m_img;
    stream >> tmp >> m_objectRect.x >> m_objectRect.y;
    stream >> tmp >> m_speed;
    stream.close();

    m_img = "img\\" + m_img;

    Gun* gun = new Gun;
    gun->init(0);
    m_guns.push_back(gun);

    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
}

void Player_AI::engage()
{
    int skipSearch = false;
    if (m_follow && chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_elapsed_engage) < m_engagementRate)
    {
        skipSearch = true;
    }
    if (!skipSearch)
    {
        int closest = world.m_SCREEN_HEIGHT*world.m_SCREEN_HEIGHT + world.m_SCREEN_WIDTH*world.m_SCREEN_WIDTH;
        int curr;
        for (int i = 0; i != world.m_enemies.size(); i++)
        {
            curr = sqrt((world.m_enemies[i]->m_objectRect.x - m_objectRect.x) * (world.m_enemies[i]->m_objectRect.x - m_objectRect.x) +
                        (world.m_enemies[i]->m_objectRect.y - m_objectRect.y) * (world.m_enemies[i]->m_objectRect.y - m_objectRect.y));
            if (curr <= closest)
            {
                closest = curr;
                m_indexOfEngagement = i;
            }
        }
    }
    m_desiredPos.x = world.m_enemies[m_indexOfEngagement]->m_objectRect.x;
    m_desiredPos.y = world.m_enemies[m_indexOfEngagement]->m_objectRect.y;
    if(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_elapsed_engage) < m_engagementRate)
    {
        m_follow = true;
    }
    else
    {
        m_follow = false;
        m_elapsed_engage = chrono::high_resolution_clock::now();
    }
}

void Player_AI::moveToTarget()
{
    m_clockwise = 1;
    if (m_speed < 2)
    {
        m_speed = 2;
    }
    if (m_speed > 5)
    {
        m_speed = 5;
    }
    int diffX = m_desiredPos.x - m_objectRect.x;
    int diffY = m_desiredPos.y - m_objectRect.y;
    if (abs(diffX) < m_speed || abs(diffY) < m_speed)
    {
        return;
    }
    double desiredAngle = asin(abs(diffX) / (sqrt((diffX)*(diffX) + (diffY)*(diffY)))) * 180.0 / PI;
    if (diffX > 0 && diffY > 0)
    {
        desiredAngle = 180 - desiredAngle;
    }
    if (diffX < 0 && diffY > 0)
    {
        desiredAngle = desiredAngle - 180;
    }
    if (diffX < 0 && diffY < 0)
    {
        desiredAngle = - desiredAngle;
    }
    if (desiredAngle < 0)
    {
        desiredAngle += 360;
    }
    if (desiredAngle > m_rotationAngle + 360 && desiredAngle - m_rotationAngle - 360 > 180)
    {
        m_clockwise = -1;
    }
    else if (desiredAngle < m_rotationAngle + 360 && m_rotationAngle + 360 - desiredAngle < 180)
    {
        m_clockwise = -1;
    }
    if (m_rotationAngle < desiredAngle)
    {
        m_rotationAngle += m_clockwise * 5;
    }
    if (m_rotationAngle > desiredAngle)
    {
        m_rotationAngle -= m_clockwise * 5;
    }
    if (m_rotationAngle > 360)
    {
        m_rotationAngle -= 360;
    }
    else if (m_rotationAngle < -360)
    {
        m_rotationAngle += 360;
    }
    if (sqrt(diffX*diffX + diffY * diffY) <= MIN_DIST)
    {
        return;
    }
    m_objectRect.x += m_speed * sin(m_rotationAngle*PI/180);
    m_objectRect.y -= m_speed * cos(m_rotationAngle*PI/180);
}

void Player_AI::shoot()
{
    for(int i = 0; i < m_guns.size() ; i++)
    {
        coordinates* buff = NULL;
        m_guns[i] -> update(m_rotationAngle, findCenter(m_objectRect, m_rotationAngle, buff));
    }
}

void Player_AI::update()
{
    m_health = 100000;
    engage();
    moveToTarget();
    shoot();
}

void Player_AI::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_objectRect, m_rotationAngle, NULL, SDL_FLIP_NONE);
}
