/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "shot_object.h"

ShotObject::ShotObject()
    : GameObject(), Radius(5.5f), Power(1) { }

ShotObject::ShotObject(glm::vec2 pos, GLfloat radius, GLint power, glm::vec2 velocity, Texture2D* sprite)
    : GameObject(pos, glm::vec2(radius * 2, radius * 2), sprite, glm::vec3(1.0f), velocity), Radius(radius), Power(power) { }

glm::vec2 ShotObject::Move(GLfloat dt)//TODO remove, GLuint window_width, glm::vec2 ShipPosition)
{
    this->Position += this->Velocity * dt;
    return this->Position;
}

GLboolean ShotObject::OutOfBounds(GLuint window_width, GLuint window_height)
{
    if (this->Position.x <= 0.0f || this->Position.x + this->Size.x >= window_width || this->Position.y <= 0.0f)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void ShotObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
}