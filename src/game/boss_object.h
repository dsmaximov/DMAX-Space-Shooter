#ifndef BOSSOBJECT_H
#define BOSSOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <chrono>

#include <irrKlang.h>
using namespace irrklang;

#include "framework/rendering/texture.h"
#include "framework/rendering/sprite_renderer.h"
#include "framework/rendering/text_renderer.h"
#include "framework/rendering/particle_generator_expl.h"
#include "framework/core/resource_manager.h"
#include "enemy_object.h"
#include "shot_object.h"

class BossObject
{
public:
    const GLint InitialStrenght = 700;
	GLint Strength;
    GLuint Stage;
	BossObject(glm::vec2* ship_position);
	void Init();
	void Draw(TextRenderer& trenderer, SpriteRenderer& renderer);
	void Move(GLfloat dt, GLuint window_width, GLuint window_height);
    bool Clean();
    std::vector <EnemyObject*> BossTurrets;
    std::vector <ShotObject*> Shots;
    ISoundEngine* SoundEngineBoss = createIrrKlangDevice();

    //BOSS turret coordinate constants
    const GLfloat DistanceBetweenRows = 40.0f;
    const int StructureCountRow0 = 6;
    const GLfloat StructureStartRow0 = 220.0;
    const GLfloat StructureSpacingRow0 = 60.0;
    const int StructureCountRow1 = 7;
    const GLfloat StructureStartRow1 = 190.0;
    const GLfloat StructureSpacingRow1 = 60.0;
    const int StructureCountRow2 = 2;
    const GLfloat StructureStartRow2 = 175.0;
    const GLfloat StructureSpacingRow2 = 395.0;
    const int StructureCountRow3 = 5; //intermediate row
    const GLfloat StructureStartRow3 = 250.0;
    const GLfloat StructureSpacingRow3 = 60.0;
    const int TurretCount1 = 4;
    const GLfloat TurretStart1 = 191.0;
    const GLfloat TurretSpacing1 = 120.0;
    const int TurretCount2 = 3;
    const GLfloat TurretStart2 = 227.0;
    const GLfloat TurretSpacing2 = 146.0;

private:
    GLfloat Stage6Angle;
    std::chrono::duration<GLint> BossTimer();
    std::chrono::steady_clock::time_point InitialTime;
    std::chrono::steady_clock::time_point CurrentTime;
    void UpdateShots(GLfloat dt, GLuint window_width, GLuint window_height);

    glm::vec2* ShipPosition;

    //Turret 0 - structure
    GLint         TURRETCOUNT0 = 9;
    GLfloat         TURRETDISTANCE0 = 60.0f;
    GLfloat       TURRETRADIUS0 = 30.0f;
    glm::vec2     TURRETVELOCITY0 = glm::vec2(0.0f, 100.0f);
    Texture2D* TURRETTEXTURE0 = ResourceManager::GetTexture("turret0");
    GLint         TURRETSTRENGHT0 = 10;
    GLint         SCOREPOINTS0 = 0;
    GLfloat       SHOTRADIUS0 = 0.0f;
    glm::vec2     SHOTVELOCITY0 = glm::vec2(0.0f, 0.0f);
    //Turret 1
    GLint         TURRETCOUNT1 = 4;
    GLfloat         TURRETDISTANCE1 = 170.0f;
    GLfloat       TURRETRADIUS1 = 30.0f;
    glm::vec2     TURRETVELOCITY1 = glm::vec2(0.0f, 100.0f);
    Texture2D*    TURRETTEXTURE1 = ResourceManager::GetTexture("turret1");
    GLint         TURRETSTRENGHT1 = 10;
    GLint         SCOREPOINTS1 = 10;
    GLfloat       SHOTRADIUS1 = 5.0f;
    glm::vec2     SHOTVELOCITY1 = glm::vec2(0.0f, 200.0f);
    //Turret 2
    GLint         TURRETCOUNT2 = 3;
    GLfloat         TURRETDISTANCE2 = 170.0f;
    GLfloat       TURRETRADIUS2 = 30.0f;
    glm::vec2     TURRETVELOCITY2 = glm::vec2(0.0f, 100.0f);
    Texture2D*    TURRETTEXTURE2 = ResourceManager::GetTexture("turret2");
    GLint         TURRETSTRENGHT2 = 10;
    GLint         SCOREPOINTS2 = 20;
    GLfloat       SHOTRADIUS2 = 5.0f;
    glm::vec2     SHOTVELOCITY2 = glm::vec2(100.0f, 200.0f);

    bool RightReached = false; //used to control oscillating movement in X
    bool LeftReached = true;
    bool BottomReached = false; //used to control oscillating movement in Y
    bool TopReached = true;
};
#endif
