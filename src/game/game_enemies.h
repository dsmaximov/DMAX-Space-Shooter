/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef GAMEENEMIES_H
#define GAMEENEMIES_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "enemy_object.h"
#include "shot_object.h"
#include "framework/rendering/sprite_renderer.h"
#include "framework/core/resource_manager.h"


/// GameLevel holds all enemies and hosts functionality to Load/render enemy levels from the harddisk.

class GameEnemies
{
public:
    // Level state
    std::vector<EnemyObject*> Enemies;
    std::vector<ShotObject*> Shots;
    // Constructor
    GameEnemies(glm::vec2 *ship_position);
    // Loads level from file
    void      Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    // Render level
    void      Draw(SpriteRenderer &renderer);
    //move all enemies
    void Move(GLfloat dt, GLuint window_width, GLuint window_height);
    // Clean destroyed enemies
    bool Clean();
//    // Check if the level is completed 
//    GLboolean IsCompleted();
private:

     // Initialize level from file data
    void init(const std::vector<std::vector<GLuint>> & tileData, GLuint levelWidth, GLuint levelHeight);
    void UpdateShots(GLfloat dt, GLuint window_width, GLuint window_height);

    glm::vec2 * ShipPosition;

    //Enemy 1
    GLfloat       ENEMYRADIUS1 = 35.0f;
    glm::vec2     ENEMYVELOCITY1 = glm::vec2 (0.0f, 100.0f);
    Texture2D*          ENEMYTEXTURE1 = ResourceManager::GetTexture("enemy1");
    GLint         ENEMYSTRENGHT1 = 10;
    GLint         SCOREPOINTS1 = 10;
    GLint         NUMBEROFSHOTS1 = 1;
    GLfloat       SHOTRADIUS1 = 5.0f;
    glm::vec2     SHOTVELOCITY1 = glm::vec2(0.0f, 200.0f);
    //Enemy 2
    GLfloat       ENEMYRADIUS2 = 35.0f;
    glm::vec2     ENEMYVELOCITY2 = glm::vec2(0.0f, 100.0f);
    Texture2D*          ENEMYTEXTURE2 = ResourceManager::GetTexture("enemy2");
    GLint         ENEMYSTRENGHT2 = 10;
    GLint         SCOREPOINTS2 = 20;
    GLint         NUMBEROFSHOTS2 = 3;
    GLfloat       SHOTRADIUS2 = 5.0f;
    glm::vec2     SHOTVELOCITY2 = glm::vec2(0.0f, 300.0f);
    //Enemy 3
    GLfloat       ENEMYRADIUS3 = 35.0f;
    glm::vec2     ENEMYVELOCITY3 = glm::vec2(0.0f, 100.0f);
    Texture2D*          ENEMYTEXTURE3 = ResourceManager::GetTexture("enemy3");
    GLint         ENEMYSTRENGHT3 = 7;
    GLint         SCOREPOINTS3 = 20;
    GLint         NUMBEROFSHOTS3 = 2;
    GLfloat       SHOTRADIUS3 = 7.0f;
    glm::vec2     SHOTVELOCITY3 = glm::vec2(0.0f, 200.0f);
    //Enemy 4
    GLfloat       ENEMYRADIUS4 = 35.0f;
    glm::vec2     ENEMYVELOCITY4 = glm::vec2(0.0f, 100.0f);
    Texture2D*       ENEMYTEXTURE4 = ResourceManager::GetTexture("enemy4");
    GLint         ENEMYSTRENGHT4 = 6;
    GLint         SCOREPOINTS4 = 20;
    GLint         NUMBEROFSHOTS4 = 2;
    GLfloat       SHOTRADIUS4 = 5.0f;
    glm::vec2     SHOTVELOCITY4 = glm::vec2(0.0f, 200.0f);
    //Enemy 5
    GLfloat       ENEMYRADIUS5 = 45.0f;
    glm::vec2     ENEMYVELOCITY5 = glm::vec2(0.0f, 100.0f);
    Texture2D*       ENEMYTEXTURE5 = ResourceManager::GetTexture("enemy5");
    GLint         ENEMYSTRENGHT5 = 5;
    GLint         SCOREPOINTS5 = 10;
    GLint         NUMBEROFSHOTS5 = 0;
    GLfloat       SHOTRADIUS5 = 5.0f;
    glm::vec2     SHOTVELOCITY5 = glm::vec2(0.0f, 200.0f);

    const GLint ENEMY_DISTANCE = 100;              //distance between enemies
    const GLint INITIALIZATION_DISTANCE = -400;     //initial distance of enemies above starting screen 

};

#endif