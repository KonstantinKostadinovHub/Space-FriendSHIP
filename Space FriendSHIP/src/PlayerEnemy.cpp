#include "PlayerEnemy.h"

PlayerEnemy::PlayerEnemy()
{
    m_rotationAngle = .0;
}

PlayerEnemy::~PlayerEnemy()
{
    //dtor
}

void PlayerEnemy::load(string config, SDL_Renderer* renderer)
{
    m_configFile = "config\\" + config;
    fstream stream;
    string tmp;
    stream.open(m_configFile.c_str());
    m_configFile = config;

    stream >> tmp >> m_objectRect.w >> m_objectRect.h;
    stream >> tmp >> m_img;
    stream >> tmp >> m_health;
    stream >> tmp >> m_collisonDamage;
    stream >> tmp >> m_attackSpeed;
    stream >> tmp >> m_speed;
    stream >> tmp >> m_bulletName;
    stream >> tmp >> m_center.x;
    stream >> tmp >> m_pointsGiven;
    stream.close();

    m_center.y = 0;
    m_img = "img\\" + m_img;

    SDL_Surface* loadingSurface = SDL_LoadBMP(m_img.c_str());
    m_objectTexture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
    SDL_FreeSurface(loadingSurface);
}

void PlayerEnemy::init(string config, coordinates coor, float rotation, Enemy* enemy, Player* player)
{
    m_configFile = enemy->m_configFile;

    m_objectRect.w = enemy->m_objectRect.w;
    m_objectRect.h = enemy->m_objectRect.h;
    m_objectRect.x = coor.x;
    m_objectRect.y = coor.y;
    m_health = enemy->m_health;
    m_collisonDamage = enemy->m_collisonDamage;
    m_attackSpeed = enemy->m_attackSpeed;
    m_objectTexture = enemy->m_objectTexture;
    m_speed = enemy->m_speed;
    m_bulletName = enemy ->m_bulletName;
    m_pointsGiven = enemy -> m_pointsGiven;
    m_target = player;

    Gun* gun = new Gun;
    gun->init(m_attackSpeed);
    m_guns.push_back(gun);
}

void PlayerEnemy::engage()
{
    m_desiredPos.x = m_target->m_objectRect.x;
    m_desiredPos.y = m_target->m_objectRect.y;
}

void PlayerEnemy::moveToTarget()
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

void PlayerEnemy::shoot()
{
    for(int i = 0; i < m_guns.size() ; i++)
    {
        coordinates playerCoor;
        coordinates* buff = NULL;
        playerCoor.x = m_objectRect.x;
        playerCoor.y = m_objectRect.y;
        m_guns[i] -> update(m_rotationAngle, findCenter(m_objectRect, m_rotationAngle, buff));
    }
}

void PlayerEnemy::update()
{
    engage();
    moveToTarget();
    shoot();
}

void PlayerEnemy::draw(SDL_Renderer* renderer)
{
    SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_objectRect, m_rotationAngle, NULL, SDL_FLIP_NONE);
}

