#ifndef HIGHSCORES_H
#define HIGHSCORES_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <tuple>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "framework/rendering/texture.h"
#include "framework/rendering/sprite_renderer.h"
#include "framework/rendering/text_renderer.h"


class HighScores
{
public:
	HighScores(const GLchar* file);
	void Draw(const GLchar* file, SpriteRenderer& srenderer, TextRenderer& renderer);
	GLuint LowestEntry();
	void InsertNewScore(GLuint);
private:
	std::pair<std::string, GLuint> ScoreList[9];
	const GLchar* File;
};
#endif
