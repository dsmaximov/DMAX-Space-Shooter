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
    GLuint Stage;
	BossObject(glm::vec2* ship_position);
	void Init();
	void Draw(TextRenderer& trenderer, SpriteRenderer& renderer);
	void Move(GLfloat dt, GLuint window_width, GLuint window_height);

    std::vector <EnemyObject*> BossTurrets;
    std::vector<ShotObject*> Shots;
private:
    std::chrono::duration<GLint> BossTimer();
    std::chrono::steady_clock::time_point InitialTime;
    std::chrono::steady_clock::time_point CurrentTime;
    void UpdateShots(GLfloat dt, GLuint window_width, GLuint window_height);

    glm::vec2* ShipPosition;

    //Turret 1
    GLint         TURRETCOUNT1 = 4;
    GLfloat         TURRETDISTANCE1 = 170.0f;
    GLfloat       TURRETRADIUS1 = 30.0f;
    glm::vec2     TURRETVELOCITY1 = glm::vec2(0.0f, 100.0f);
    Texture2D*    TURRETTEXTURE1 = ResourceManager::GetTexture("enemy1");
    GLint         TURRETSTRENGHT1 = 10;
    GLint         SCOREPOINTS1 = 10;
    GLfloat       SHOTRADIUS1 = 5.0f;
    glm::vec2     SHOTVELOCITY1 = glm::vec2(0.0f, 200.0f);
    //Turret 2
    GLint         TURRETCOUNT2 = 3;
    GLfloat         TURRETDISTANCE2 = 170.0f;
    GLfloat       TURRETRADIUS2 = 30.0f;
    glm::vec2     TURRETVELOCITY2 = glm::vec2(0.0f, 100.0f);
    Texture2D*    TURRETTEXTURE2 = ResourceManager::GetTexture("enemy2");
    GLint         TURRETSTRENGHT2 = 10;
    GLint         SCOREPOINTS2 = 20;
    GLfloat       SHOTRADIUS2 = 5.0f;
    glm::vec2     SHOTVELOCITY2 = glm::vec2(0.0f, 200.0f);

    bool RightReached = false; //used to control oscillating movement in X
    bool LeftReached = true;
};
#endif
