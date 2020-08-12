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

#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "framework/rendering/texture.h"
#include "framework/rendering/sprite_renderer.h"
#include "framework/rendering/text_renderer.h"


class MenuButton
{
public:

	MenuButton(Shader* shader, Texture2D* btexture, Texture2D* atexture, std::string text);
	bool Activate();
	bool Deactivate();
	bool Press();
	bool UnPress();
	void Draw(SpriteRenderer& srenderer, TextRenderer& renderer, glm::vec2 pos, glm::vec2 size);

	bool ButtonAvailable = false;
	bool ButtonActive = false;
	bool ButtonPressed = false;
	
private:
	std::string Text;
	Texture2D* ButtonTexture;
	Texture2D* ActivationTexture;
};
#endif 

