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

#ifndef GAMESHOTS_H
#define GAMESHOTS_H

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <algorithm> 

#include <irrKlang.h>

#include "shot_object.h"
#include "framework/rendering/texture.h"
#include "framework/rendering/sprite_renderer.h"
#include "framework/core/resource_manager.h"
using namespace irrklang;

class GameShots
{
public:
	//Constructor
	GameShots();
	//new shot created
	void NewShot(glm::vec2 pos, GLfloat radius, GLint power, glm::vec2 velocity, Texture2D* sprite);
	//render all shots
	void Draw(SpriteRenderer& renderer);
	//move all shots
	void Move(GLfloat dt, GLuint window_width, GLuint window_height, glm::vec2 pos);
	std::vector <ShotObject*>Shots;
	void Clean();
private:
};
#endif