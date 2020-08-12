/************************************************************************
** This code is part of DMAX_Shooter.
**
** DMAX_Shooter is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
** It is based on https://github.com/Shot511/GameBreakout.
** Implementation of https://learnopengl.com/In-Practice/2D-Game/Breakout
*************************************************************************/

#ifndef POWER_UP_H
#define POWER_UP_H
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"

// PowerUp inherits its state and rendering functions from
// GameObject but also holds extra information to state its
// active duration and whether it is activated or not.
// The type of PowerUp is stored as a string.
class PowerUp : public GameObject
{
public:
    // PowerUp State
    GLint Type;
    GLboolean Activated;
    glm::vec2 OriginalSize;
    // Constructor
    PowerUp(GLint type, glm::vec3 color, glm::vec2 position, glm::vec2 velocity, glm::vec2 size, Texture2D * texture)
            : GameObject(position, size, texture, color, velocity), Type(type), Activated(), OriginalSize(size) { }
    glm::vec2 Move(GLfloat dt, GLuint window_height);
private:
    GLfloat PulseCoeff = 1.0f;
};

#endif