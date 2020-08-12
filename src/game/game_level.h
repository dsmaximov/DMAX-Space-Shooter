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

#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "framework/rendering/sprite_renderer.h"
#include "framework/core/resource_manager.h"


/// GameLevel holds all Tiles as part of a Breakout level and
/// hosts functionality to Load/render levels from the harddisk.
class GameLevel
{
public:
    // Level state
    std::vector<GameObject> Bricks;
    // Constructor
    GameLevel() { }
    // Loads level from file
    void      Load(const GLchar *file, GLuint levelWidth, GLuint levelHeight);
    // Render level
    void      Draw(SpriteRenderer &renderer);
    // Check if the level is completed (all non-solid tiles are destroyed)
    GLboolean IsCompleted();
private:
    // Initialize level from tile data
    void      init(const std::vector<std::vector<GLuint>> & tileData, GLuint levelWidth, GLuint levelHeight);
};

#endif