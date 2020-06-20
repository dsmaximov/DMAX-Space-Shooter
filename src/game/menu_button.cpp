#include "menu_button.h"

MenuButton::MenuButton(Shader* shader, Texture2D* btexture, Texture2D* atexture, std::string text) : ButtonTexture(btexture), ActivationTexture(atexture), Text(text) {}
bool MenuButton::Activate()
{
	ButtonActive = true;
	return ButtonActive;
}
bool MenuButton::Deactivate()
{
	ButtonActive = false;
	return ButtonActive;
}

bool MenuButton::Press()
{
	ButtonPressed = true;
	return ButtonPressed;
}
bool MenuButton::UnPress()
{
	ButtonPressed = false;
	return ButtonPressed;
}

void MenuButton::Draw(SpriteRenderer& srenderer, TextRenderer& trenderer, glm::vec2 pos, glm::vec2 size)
{
	const glm::vec3 TEXTCOLOR = glm::vec3(.7f, .7f, .7f);
	GLfloat UnavalableButtonColor = .3f + ButtonAvailable * .7f; //make button darker if unavailable
	srenderer.DrawSprite(ButtonTexture, pos, size);
	trenderer.RenderText(Text, pos.x+size.x*.15f, pos.y+size.y*.3f, 1.0f, TEXTCOLOR*UnavalableButtonColor);
	if (ButtonActive) srenderer.DrawSprite(ActivationTexture, pos, size); //if button is selected
}