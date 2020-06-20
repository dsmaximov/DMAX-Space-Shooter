#include "game_shots.h"

GameShots::GameShots()
    : Shots{ new ShotObject(glm::vec2(0,0), 0.0f, 0,glm::vec2(0,0),ResourceManager::GetTexture("paddle")) } { }

void GameShots::NewShot(glm::vec2 pos, GLfloat radius, GLint power, glm::vec2 velocity, Texture2D* sprite)
{

    Shots.push_back(new ShotObject(pos, radius, power, velocity, sprite));
}
void GameShots::Draw(SpriteRenderer& renderer)
{
    for (auto n : Shots)
    {
        if (n!=NULL) n->Draw(renderer);
    }
}
void GameShots::Move(GLfloat dt, GLuint window_width, GLuint window_height, glm::vec2 pos)
{
    for (auto n : Shots)
    {
        n->Move(dt, window_width, pos);    
    }
    for (auto it = Shots.begin(); it != Shots.end(); /*nothing*/)
    {
        if ((*it)->OutOfBounds(window_width, window_height) == true)
        {
            it = Shots.erase(it);
        }
        else
        {
            it++;
        }
    }
}
void GameShots::Clean()
{
   Shots.erase(std::remove_if(Shots.begin(), Shots.end(), [](ShotObject* shot)->bool {return shot->Power < 1; }), Shots.end()); //
}