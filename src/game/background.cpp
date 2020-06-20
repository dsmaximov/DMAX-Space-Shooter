/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "background.h"

Background::Background() :  Position(0, 0), Texture(ResourceManager::GetTexture("background")), Height(0), Width(0){}

Background::Background(glm::vec2 pos, Texture2D* sprite,  GLint width, GLint height) : Position(pos), Texture(sprite), Height(height), Width(width) { }

glm::vec2 Background::Move(GLfloat dt, GLfloat scroll_speed, GLuint window_height, glm::vec2 screen_position)
{
    Position.y += scroll_speed * dt;
    if (Position.y > window_height)
    {
        this->Reset(screen_position);
    }
    return Position;
}
void Background::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(Texture, glm::vec2(Position.x, Position.y-Height), glm::vec2(Width, Height*2) );
}

// Resets the screen to initial Stuck Position (if ball is outside window bounds)
void Background::Reset(glm::vec2 position)
{
    this->Position = position;
}