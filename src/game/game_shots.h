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