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
