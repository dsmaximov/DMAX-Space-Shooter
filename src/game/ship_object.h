/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef SHIPOBJECT_H
#define SHIPOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "framework/rendering/texture.h"
#include "framework/rendering/sprite_renderer.h"
#include "framework/core/resource_manager.h"
#include "power_up.h"

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class ShipObject : public GameObject
{
public:
    // Ball state
    GLfloat   Radius;
    GLboolean Invulnerable;
    GLint Shields;
    GLint WeaponType;
    GLint WeaponPower;
    // Constructor(s)
    ShipObject();
    ShipObject(glm::vec2 pos, glm::vec2 radius, glm::vec2 velocity, Texture2D * sprite);
    glm::vec2 ShipObject::FiringPosition();
    void Reset(glm::vec2 ShipPosition);
    void Draw(SpriteRenderer& renderer, GLuint shields);
};

#endif