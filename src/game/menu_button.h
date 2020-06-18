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

