#include "game_enemies.h"

#include <fstream>
#include <sstream>

GameEnemies::GameEnemies(glm::vec2 *ship_position) :  ShipPosition(ship_position){ }

void GameEnemies::Load(const GLchar* file, GLuint levelWidth, GLuint levelHeight)
{
    // Clear old data
    this->Enemies.clear();
    // Load from file
    GLuint EnemyCode;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<GLuint>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // Read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> EnemyCode) // Read each word seperated by spaces
                row.push_back(EnemyCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}
void GameEnemies::init(const std::vector<std::vector<GLuint>>& tileData, GLuint levelWidth, GLuint levelHeight)
{
    // Calculate dimensions
    GLuint enemy_lines = tileData.size();
    GLuint enemy_ships_per_line = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
    //TODO delete GLfloat unit_width = levelWidth / static_cast<GLfloat>(enemy_ships_per_line), unit_height = levelHeight / enemy_lines;
    // Initialize level tiles based on tileData
    for (GLint y = 0; y < enemy_lines; ++y)
    {
        for (GLint x = 0; x < enemy_ships_per_line; ++x)
        {
            // Check block type from level data (2D level array)
            if (tileData[y][x] == 1) // Solid
            {
                glm::vec2 pos(ENEMY_DISTANCE * x, INITIALIZATION_DISTANCE - ENEMY_DISTANCE * y); //start above the visible screen
                this->Enemies.push_back(new EnemyObject(pos, ENEMYRADIUS1, ENEMYVELOCITY1, ENEMYTEXTURE1, ENEMYSTRENGHT1, SCOREPOINTS1, 1, NUMBEROFSHOTS1, SHOTVELOCITY1));
            }
            if (tileData[y][x] == 2) // Solid
            {
                glm::vec2 pos(ENEMY_DISTANCE * x, INITIALIZATION_DISTANCE - ENEMY_DISTANCE * y); //- levelHeight * 2); //start above the visible screen
                this->Enemies.push_back(new EnemyObject(pos, ENEMYRADIUS2, ENEMYVELOCITY2, ENEMYTEXTURE2, ENEMYSTRENGHT2, SCOREPOINTS2, 2, NUMBEROFSHOTS2, SHOTVELOCITY2));
            }
            if (tileData[y][x] == 3) // Solid
            {
                glm::vec2 pos(ENEMY_DISTANCE * x, INITIALIZATION_DISTANCE - ENEMY_DISTANCE * y); //- levelHeight * 2); //start above the visible screen
                this->Enemies.push_back(new EnemyObject(pos, ENEMYRADIUS3, ENEMYVELOCITY3, ENEMYTEXTURE3, ENEMYSTRENGHT3, SCOREPOINTS3, 3, NUMBEROFSHOTS3, SHOTVELOCITY3));
            }
            if (tileData[y][x] == 4) // Solid
            {
                glm::vec2 pos(ENEMY_DISTANCE * x, INITIALIZATION_DISTANCE - ENEMY_DISTANCE * y); //- levelHeight * 2); //start above the visible screen
                this->Enemies.push_back(new EnemyObject(pos, ENEMYRADIUS4, ENEMYVELOCITY4, ENEMYTEXTURE4, ENEMYSTRENGHT4, SCOREPOINTS4, 4, NUMBEROFSHOTS4, SHOTVELOCITY4));
            }
            if (tileData[y][x] == 5) // Solid
            {
                glm::vec2 pos(ENEMY_DISTANCE * x, INITIALIZATION_DISTANCE - ENEMY_DISTANCE * y); //- levelHeight * 2); //start above the visible screen
                this->Enemies.push_back(new EnemyObject(pos, ENEMYRADIUS5, ENEMYVELOCITY5, ENEMYTEXTURE5, ENEMYSTRENGHT5, SCOREPOINTS5, 5, NUMBEROFSHOTS5, SHOTVELOCITY5));
            }

        }
    }
}
void GameEnemies::Draw(SpriteRenderer& renderer)
{
    for (auto n : this->Enemies)
    {
        renderer.DrawSprite(n->Sprite, n->Position, n->Size, n->Rotation, n->Color); //render enemy
        switch (n->Strenght) // render shields
        {
        case 10:
            renderer.DrawSprite(ResourceManager::GetTexture("shield"), n->Position - n->Size * 0.05f, n->Size * 1.1f, n->Rotation, glm::vec3(.5f, 1.0f, 1.0f));
            break;
        case 9:
            renderer.DrawSprite(ResourceManager::GetTexture("shield"), n->Position - n->Size * 0.05f, n->Size * 1.1f, n->Rotation, glm::vec3(.5f, .8f, .9f));
            break;
        case 8:
            renderer.DrawSprite(ResourceManager::GetTexture("shield"), n->Position - n->Size * 0.05f, n->Size * 1.1f, n->Rotation, glm::vec3(.5f, .8f, .8f));
            break;
        case 7:
            renderer.DrawSprite(ResourceManager::GetTexture("shield"), n->Position - n->Size * 0.05f, n->Size * 1.1f, n->Rotation, glm::vec3(.5f, .7f, .7f));
            break;
        case 6:
            renderer.DrawSprite(ResourceManager::GetTexture("shield"), n->Position - n->Size * 0.05f, n->Size * 1.1f, n->Rotation, glm::vec3(.5f, .6f, .6f));
            break;
        case 5:
            renderer.DrawSprite(ResourceManager::GetTexture("shield"), n->Position - n->Size * 0.05f, n->Size * 1.1f, n->Rotation, glm::vec3(.5f, .5f, .5f));
            break;
        case 4:
            renderer.DrawSprite(ResourceManager::GetTexture("shield"), n->Position - n->Size * 0.05f, n->Size * 1.1f, n->Rotation, glm::vec3(.5f, .4f, .4f));
            break;
        case 3:
            renderer.DrawSprite(ResourceManager::GetTexture("shield"), n->Position - n->Size * 0.05f, n->Size * 1.1f, n->Rotation, glm::vec3(.5f, .3f, .3f));
            break;
        case 2:
            renderer.DrawSprite(ResourceManager::GetTexture("shield"), n->Position - n->Size * 0.05f, n->Size * 1.1f, n->Rotation, glm::vec3(.5f, .2f, .2f));
            break;
        }
    }
    for (auto n : this->Shots)
    {
        n->Draw(renderer);
    }
}
void GameEnemies::Move(GLfloat dt, GLuint window_width, GLuint window_height)
{
    for (auto n : Enemies)
    {
        n->Move(dt, window_width);
    }
    for (auto it = Enemies.begin(); it != Enemies.end(); /*nothing*/)
    {
        if ((*it)->Position.y>window_height)
        {
            it = Enemies.erase(it);
        }
        else
        {
            it++;
        }
    }
    UpdateShots(dt, window_width, window_height);
}

void GameEnemies::UpdateShots(GLfloat dt, GLuint window_width, GLuint window_height)
{
    for (auto n : this->Enemies) //create shots
    {
        switch (n->Type)
        {
        case 3:
        {
            GLfloat Speed = sqrt(SHOTVELOCITY3.x * SHOTVELOCITY3.x + SHOTVELOCITY3.y * SHOTVELOCITY3.y); //determine the magnitude of velocity
            GLfloat DistX = ShipPosition->x - n->Position.x;
            GLfloat DistY = ShipPosition->y - n->Position.y;
            glm::vec2 Direction = glm::vec2(DistX / sqrt(DistX * DistX + DistY * DistY), DistY / sqrt(DistX * DistX + DistY * DistY)); //determine the direction of velocity - aim towards the ship
            glm::vec2 ShotVelocity3 = glm::vec2(Speed * Direction);
            if (n->Position.y > 100 && n->NumberOfShots == 2)
            {
                Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS3, 1, ShotVelocity3, ResourceManager::GetTexture("shot1")));
                n->NumberOfShots--;
            }
            if (n->Position.y > 200 && n->NumberOfShots == 1)
            {
                Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS3, 1, ShotVelocity3, ResourceManager::GetTexture("shot1")));
                n->NumberOfShots--;
            }
        }
            break;
        case 2:
            if (n->Position.y > 100 && n->NumberOfShots == 3 )
            {
                Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(SHOTVELOCITY2.x + 100, SHOTVELOCITY2.y), 
                    ResourceManager::GetTexture("shot1")));
                Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(SHOTVELOCITY2.x - 100, SHOTVELOCITY2.y), 
                    ResourceManager::GetTexture("shot1")));
                n->NumberOfShots--;
            }
            if (n->Position.y > 200 && n->NumberOfShots == 2 )
            {
                Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(SHOTVELOCITY2.x + 100, SHOTVELOCITY2.y), 
                    ResourceManager::GetTexture("shot1")));
                Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(SHOTVELOCITY2.x - 100, SHOTVELOCITY2.y), 
                    ResourceManager::GetTexture("shot1")));
                n->NumberOfShots--;
            }
            if (n->Position.y > 300 && n->NumberOfShots == 1 )
            {
                Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(SHOTVELOCITY2.x + 100, SHOTVELOCITY2.y), 
                    ResourceManager::GetTexture("shot1")));
                Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS2, 1, glm::vec2(SHOTVELOCITY2.x - 100, SHOTVELOCITY2.y), 
                    ResourceManager::GetTexture("shot1")));
                n->NumberOfShots--;
            }
            break;
        case 1:
            if (n->Position.y > 100 && n->NumberOfShots > 0)
            {
                Shots.push_back(new ShotObject(glm::vec2(n->FiringPosition().x - 5.0f, n->FiringPosition().y + n->Size.y), SHOTRADIUS1, 1, SHOTVELOCITY1, ResourceManager::GetTexture("shot1")));
                n->NumberOfShots--;
            }
            break;
        }

    }
    for (auto n : Shots)
    {
        n->Move(dt, window_width, glm::vec2(100.0f, 100.0f));
    }
    for (auto it = Shots.begin(); it != Shots.end(); /*nothing*/) //erase shots
    {
        if ((*it)->Position.y > window_height || (*it)->Position.y < 0 || (*it)->Position.x > window_width || (*it)->Position.x < 0 || (*it)->Power<1)
        {
            it = Shots.erase(it);
        }
        else
        {
            it++;
        }
    }
}


bool GameEnemies::Clean()
{
    auto last = std::remove_if(Enemies.begin(), Enemies.end(), [](EnemyObject* enemy)->bool {return enemy->Strenght < 1; });
    if (last == Enemies.end())
    {
        return false;
    }
    else
    {
        Enemies.erase(last, Enemies.end());
        return true;
    }
}