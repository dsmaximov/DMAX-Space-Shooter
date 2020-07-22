/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef ENEMYOBJECT_H
#define ENEMYOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "framework/rendering/texture.h"

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class EnemyObject : public GameObject
{
public:
    // Enemy state
    GLfloat Radius;
    GLint Strength;
    GLint Type;
    GLint ScorePoints;
    GLint NumberOfShots;
    glm::vec2 ShotVelocity;
    // Constructor(s)
    EnemyObject();
    EnemyObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D * sprite, GLint strenght, GLint scorepoints, GLint type, GLint number_of_shots, glm::vec2 shot_velocity);
    // Position where the shots come from
    glm::vec2 EnemyObject::FiringPosition();
    // Moves the ball, keeping it constrained within the window bounds (except bottom edge); returns new position
    glm::vec2 EnemyObject::Move(GLfloat dt, GLuint window_width);
private:

    const GLfloat HORIZONTAL_VELOCITY1 = 0.0f;
    const GLfloat HORIZONTAL_VELOCITY2 = 100.0f;
    const GLfloat HORIZONTAL_VELOCITY3 = 0.0f;
    const GLfloat HORIZONTAL_VELOCITY4 = 100.0f;
    const GLfloat HORIZONTAL_VELOCITY5 = 0.0f;
    bool MaxXvelocityReachedRight2 = true; //used to control oscillating movement in X for enemy 2
    bool MaxXvelocityReachedLeft2 = false;
};

#endif