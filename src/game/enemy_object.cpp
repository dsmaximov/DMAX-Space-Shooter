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
    : GameObject(), Radius(0.0f), Strength(0), Type(0) { }

EnemyObject::EnemyObject(glm::vec2 pos, GLfloat radius, glm::vec2 velocity, Texture2D* sprite, GLint strenght, GLint scorepoints, GLint type, GLint number_of_shots, glm::vec2 shot_velocity)
    : GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), Radius(radius), Strength(strenght), ScorePoints(scorepoints), 
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
        if (this->Velocity.x > HORIZONTAL_VELOCITY2 * 1.5f) { MaxXvelocityReachedRight2 = true; MaxXvelocityReachedLeft2 = false; }
        if (this->Velocity.x < -HORIZONTAL_VELOCITY2 * 1.5f) { MaxXvelocityReachedLeft2 = true; MaxXvelocityReachedRight2 = false; }
        if (this->Position.y > 0)
        {
            WobbleXcoeff = this->Position.y / 10;
        }
        if (MaxXvelocityReachedLeft2)
        {
            Velocity.x += (HORIZONTAL_VELOCITY2 + WobbleXcoeff) * dt;
        }
        if (MaxXvelocityReachedRight2)
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

    case 4: // type 4 - acceleration in y
        if (this->Position.y > 0)
        {
            this->Velocity.y += this->Position.y * dt;
        }
        this->Position += this->Velocity * dt;
        return this->Position;
        break;

    case 5: // type 5 - straight down in y
        this->Position += this->Velocity * dt;
        return this->Position;
        break;
    }
}