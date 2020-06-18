/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "framework/rendering/texture.h"
#include "framework/rendering/sprite_renderer.h"
#include "framework/core/resource_manager.h"

class Background
{
public:
    Texture2D* Texture;
    glm::vec2 Position;
    GLint Height;
    GLint Width;
    // Constructor(s)
    Background();
    Background(glm::vec2 pos, Texture2D* sprite, GLint height, GLint width);
    // Moves the background
    glm::vec2 Move(GLfloat dt, GLfloat scroll_speed, GLuint window_height, glm::vec2 screen_position);
    //render background
    void Draw(SpriteRenderer& renderer);
    // Resets the ship to original state with given position and velocity
    void Reset(glm::vec2 screen_position);
};

#endif