#ifndef BOSSOBJECT_H
#define BOSSOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <chrono>

#include "framework/rendering/texture.h"
#include "framework/rendering/sprite_renderer.h"
#include "framework/rendering/text_renderer.h"
#include "framework/core/resource_manager.h"
#include "enemy_object.h"
#include "shot_object.h"

class BossObject
{
public:
	GLuint Strength;
	BossObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D* sprite);
	void Init();
	void Draw(TextRenderer& trenderer, SpriteRenderer& renderer);
	void Update(GLfloat dt);
private:
	
    std::vector <EnemyObject*> BossTurrets;
    std::chrono::duration<GLint> BossTimer();
    std::chrono::steady_clock::time_point InitialTime;
    std::chrono::steady_clock::time_point CurrentTime;

    //Turret 1
    GLfloat       ENEMYRADIUS1 = 35.0f;
    glm::vec2     ENEMYVELOCITY1 = glm::vec2(0.0f, 100.0f);
    Texture2D*    ENEMYTEXTURE1 = ResourceManager::GetTexture("enemy1");
    GLint         ENEMYSTRENGHT1 = 10;
    GLint         SCOREPOINTS1 = 10;
    GLfloat       SHOTRADIUS1 = 5.0f;
    glm::vec2     SHOTVELOCITY1 = glm::vec2(0.0f, 200.0f);
    //Turret 2
    GLfloat       ENEMYRADIUS2 = 35.0f;
    glm::vec2     ENEMYVELOCITY2 = glm::vec2(0.0f, 100.0f);
    Texture2D*    ENEMYTEXTURE2 = ResourceManager::GetTexture("enemy2");
    GLint         ENEMYSTRENGHT2 = 10;
    GLint         SCOREPOINTS2 = 20;
    GLfloat       SHOTRADIUS2 = 5.0f;
    glm::vec2     SHOTVELOCITY2 = glm::vec2(0.0f, 200.0f);
};
#endif
