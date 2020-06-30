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
	void Draw(); 
	GLuint LowestEntry();
	void InsertNewScore(GLuint new_high_score);
	std::string AddInitials(GLint &keycode, int &keyaction, GLuint new_high_score);
	GLboolean NewHighScore;
private:
	std::pair<std::string, GLuint> ScoreList[9];
	const GLchar* File;
	SpriteRenderer& Srenderer;
	TextRenderer& Trenderer;
	GLuint ScoreListSize;
	std::string Initials[3] = {"","",""};
	//button triggers
	bool ButtonPressed = false;
	bool ButtonReleased = false;
	//enter initials state machine
	bool InitialState = true; //press Enter to start
	bool InitialStateComplete = false;
	bool FirstLetter = false;
	bool SecondLetter = false;
	bool ThirdLetter = false;
	bool AllLettersReady = false;
	int LetterNumber = 0; //

};
#endif
