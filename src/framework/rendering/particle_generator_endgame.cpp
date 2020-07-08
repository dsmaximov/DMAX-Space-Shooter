/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "particle_generator_endgame.h"

ParticleGeneratorEndgame::ParticleGeneratorEndgame(Shader * shader, Texture2D * texture, GLuint amount, GameObject& object, GLuint newParticles, glm::vec2 offset, glm::vec4 color, GLfloat duration)
        : shader(shader), texture(texture), amount(amount), object(object), newparticles(newParticles), offset(offset), generator_life(duration), color(color)
{
    this->init();
}

void ParticleGeneratorEndgame::Update(GLfloat dt)
{
    // Add new particles
    generator_life -= dt;
    for (GLuint i = 0; i < newparticles; ++i)
    {
        int unusedParticle = this->firstUnusedParticle();
        this->respawnParticle(this->particles[unusedParticle], object, offset);
    }
    // Update all particles
    for (GLuint i = 0; i < this->amount; ++i)
    {
        ParticleEnd&p = this->particles[i];
        p.Life -= dt; // reduce life
        if (p.Life > 0.0f)
        {	// particle is alive, thus update
            GLfloat randR = (rand() % 100) / 100.0f;
            GLfloat randG = (rand() % 100) / 100.0f;
            GLfloat randB = (rand() % 100) / 100.0f;
            p.Position.x -= p.Velocity.x * dt;
            p.Position.y -= p.Velocity.y * dt;
            p.Color = glm::vec4(color.x*randR, color.y*randG, color.z*randB, p.Life);
        }
    }

}

// Render all particles
void ParticleGeneratorEndgame::Draw()
{
    // Use additive blending to give it a 'glow' effect
    if (generator_life > 0.0f)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        this->shader->Use();
        for (ParticleEnd particle : this->particles)
        {
            if ((particle.Life > 0.0f))
            {
                //iterations++;
                this->shader->SetVector2f("offset", particle.Position);
                this->shader->SetVector4f("color", particle.Color);
                this->texture->Bind();
                glBindVertexArray(this->VAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindVertexArray(0);
            }
        }
        // Don't forget to reset to default blending mode
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}

void ParticleGeneratorEndgame::init()
{
    // Set up mesh and attribute properties
    GLuint VBO;
    GLfloat particle_quad[] = {
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(this->VAO);
    // Fill mesh buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
    // Set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glBindVertexArray(0);

    // Create this->amount default particle instances
    for (GLuint i = 0; i < this->amount; ++i)
        this->particles.push_back(ParticleEnd());
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle2 = 0;
GLuint ParticleGeneratorEndgame::firstUnusedParticle()
{
    // First search from last used particle, this will usually return almost instantly
    for (GLuint i = lastUsedParticle2; i < this->amount; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle2 = i;
            return i;
        }
    }
    // Otherwise, do a linear search
    for (GLuint i = 0; i < lastUsedParticle2; ++i){
        if (this->particles[i].Life <= 0.0f){
            lastUsedParticle2 = i;
            return i;
        }
    }
    // All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
    lastUsedParticle2 = 0;
    return 0;
}

void ParticleGeneratorEndgame::respawnParticle(ParticleEnd&particle, GameObject &object, glm::vec2 offset)
{
    GLfloat randposX = ((rand() % 100) - 50) / 15.0f;
    GLfloat randposY = ((rand() % 100) - 50) / 15.0f;
    GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
    particle.Position = object.Position + glm::vec2(randposX, randposY) + offset;
    particle.Life = generator_life;
    particle.Color = glm::vec4(rColor, rColor, rColor, particle.Life);
    particle.Velocity = glm::vec2(randposX*50, randposY*50);
}