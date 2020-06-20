/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "enemy_object.h"

EnemyObject::EnemyObject()
    : GameObject(), Radius(0.0f), Strenght(0), Type(0) { }

EnemyObject::EnemyObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D* sprite, GLint strenght, GLint scorepoints, GLint type, GLint number_of_shots, glm::vec2 shot_velocity)
    : GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), Radius(radius), Strenght(strenght), ScorePoints(scorepoints), 
    Type(type), NumberOfShots(number_of_shots), ShotVelocity(shot_velocity) { }


glm::vec2 EnemyObject::FiringPosition()
{
    float centeredX = this->Position.x + this->Size.x / 2;
    glm::vec2 FPos(centeredX, this->Position.y);
    return FPos; 
}
glm::vec2 EnemyObject::Move(GLfloat dt, GLuint window_width)
{
    switch (Type)
    {
    case 1: // type 1 - straight down in y
        this->Position += this->Velocity * dt;
        return this->Position;
        break;

    case 2: // type 2 - wobbling motion in X
    {    GLfloat WobbleXcoeff = 0.0f;
        if (this->Velocity.x > HORIZONTAL_VELOCITY2 * 1.5f) { MaxXvelocityReachedRight = true; MaxXvelocityReachedLeft = false; }
        if (this->Velocity.x < -HORIZONTAL_VELOCITY2 * 1.5f) { MaxXvelocityReachedLeft = true; MaxXvelocityReachedRight = false; }
        if (this->Position.y > 0)
        {
            WobbleXcoeff = this->Position.y / 10;
        }
        if (MaxXvelocityReachedLeft)
        {
            Velocity.x += (HORIZONTAL_VELOCITY2 + WobbleXcoeff) * dt;
        }
        if (MaxXvelocityReachedRight)
        {
            Velocity.x -= (HORIZONTAL_VELOCITY2 + WobbleXcoeff) * dt;
        }
        this->Position += this->Velocity * dt;
        return this->Position;
    }
        break;

    case 3: // type 3 - straight down in y
        this->Position += this->Velocity * dt;
        return this->Position;
        break;

    case 4: // type 4 - straight down in y
        this->Position += this->Velocity * dt;
        return this->Position;
        break;

    case 5: // type 5 - straight down in y
        this->Position += this->Velocity * dt;
        return this->Position;
        break;
    }
}