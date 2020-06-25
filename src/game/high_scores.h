#ifndef HIGHSCORES_H
#define HIGHSCORES_H


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
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
	HighScores(const GLchar* file, SpriteRenderer& srenderer, TextRenderer& trenderer);
	void Draw(const GLchar* file, SpriteRenderer& srenderer, TextRenderer& renderer); //TODO remove file, srenderer, trenderer
	GLuint LowestEntry();
	void InsertNewScore(GLuint);
	std::string AddInitials(GLint &keycode, int &keyaction);
private:
	std::pair<std::string, GLuint> ScoreList[9];
	const GLchar* File;
	SpriteRenderer& Srenderer;
	TextRenderer& Trenderer;
	GLuint ScoreListSize;
	std::string Initials[3] = {"","",""};
	bool ButtonPressed = false;
	int InitialNumber = 0;
};
#endif
