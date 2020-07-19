/******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "ship_object.h"

ShipObject::ShipObject()
    : GameObject(), Invulnerable(GL_FALSE), Radius(400), Shields (10), WeaponType(0), WeaponPower(0){ }

ShipObject::ShipObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, Texture2D* sprite)
    : GameObject(pos, size, sprite, glm::vec3(1.0f), velocity), Invulnerable(GL_FALSE), Radius(size.x/2), Shields(10), WeaponType(0), WeaponPower(0){ }


glm::vec2 ShipObject::FiringPosition()
{
    float centeredX = this->Position.x + this->Size.x / 2;
    glm::vec2 FPos(centeredX, this->Position.y);
    return FPos; 
}
void ShipObject::Draw(SpriteRenderer& renderer, GLuint shields)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
    if (!this->Invulnerable)
    {
        renderer.DrawSprite(ResourceManager::GetTexture("shield"), this->Position - this->Size * 0.1f, this->Size * 1.2f, this->Rotation, glm::vec3(0.7f, shields / 10.0f, shields / 10.0f));
    }

}

// Resets the ball to initial Stuck Position (if ball is outside window bounds)
void ShipObject::Reset(glm::vec2 position)
{
    this->Position = position;
}