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

#ifndef PARTICLE_GENERATOR_EXPLOSION_H
#define PARTICLE_GENERATOR_EXPLOSION_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "shader.h"
#include "texture.h"
#include "game/game_object.h"


// Represents a single particle and its state
struct ParticleExplosion {
    glm::vec2 Position, Velocity;
    glm::vec4 Color;
    GLfloat Life;

    ParticleExplosion() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};


// ParticleGenerator acts as a container for rendering a large number of
// particles by repeatedly spawning and updating particles and killing
// them after a given amount of time.
class ParticleGeneratorExplosion
{
public:
    // Constructor
    ParticleGeneratorExplosion(Shader * shader, Texture2D * texture, GLuint amount, GameObject& object, GLuint newParticles, glm::vec2 offset, glm::vec4 color, GLfloat duration);
    // Update all particles
    void Update(GLfloat dt);
    // Render all particles
    void Draw();
    int iterations = 0;
    GLfloat generator_life; //how soon is the generator destroyed i.e. -> duration of explosion
private:
    // State
    std::vector<ParticleExplosion> particles;
    GLuint amount;
    // Render state
    Shader * shader;
    Texture2D * texture;
    GLuint VAO;
    GameObject& object;
    GLuint newparticles;
    glm::vec2 offset;
    glm::vec4 color;
    
    // Initializes buffer and vertex attributes
    void init();
    // Returns the first Particle index that's currently unused e.g. Life <= 0.0f or 0 if no particle is currently inactive
    GLuint firstUnusedParticle();
    // Respawns particle
    void respawnParticle(ParticleExplosion &particle, GameObject &object, glm::vec2 offset = glm::vec2(0.0f, 0.0f));
};

#endif