/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef SHOTOBJECT_H
#define SHOTOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "framework/rendering/texture.h"
#include "power_up.h"

// BallObject holds the state of the Ball object inheriting
// relevant state data from GameObject. Contains some extra
// functionality specific to Breakout's ball object that
// were too specific for within GameObject alone.
class ShotObject : public GameObject
{
public:
    // Ball state
    GLfloat Radius;
    GLint Power;
    // Constructor(s)
    ShotObject();
    ShotObject(glm::vec2 pos, GLfloat radius, GLint power, glm::vec2 velocity, Texture2D* sprite);
    // Moves the shot
    glm::vec2 Move(GLfloat dt);//TODO remove, GLuint window_width, glm::vec2 ShipPosition);
    // Returns true if shot is out of screen
    GLboolean OutOfBounds(GLuint window_width, GLuint window_height);
    // Resets the ball to original state with given position and velocity
    void      Reset(glm::vec2 position, glm::vec2 velocity);
};

#endif
