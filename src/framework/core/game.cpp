/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include <algorithm>
#include <sstream>
#include <vector>
#include <GLFW/glfw3.h>

#include <irrKlang.h>
using namespace irrklang;

#include "game.h"
#include "resource_manager.h"
#include "framework/rendering/sprite_renderer.h"
#include "framework/rendering/particle_generator.h"
#include "framework/rendering/particle_generator_expl.h"
#include "framework/rendering/post_processor.h"
#include "framework/rendering/text_renderer.h"
#include "game/ball_object.h"
#include "game/ship_object.h"
#include "game/shot_object.h"
#include "game/game_shots.h"
#include "game/background.h"
#include "game/enemy_object.h"
#include "game/menu_button.h"
#include "game/power_up.h"

// Game-related State data
SpriteRenderer    * Renderer;
//GameObject        * Player;
//BallObject        * Ball;
//BallObject        * Ball_1;
//ShotObject        * Shot;
//std::vector <BallObject*> AllBalls;
//std::vector <ShotObject*> AllShots;
ShipObject        * Ship;
ParticleGenerator * ParticlesEngineLeft;
ParticleGenerator * ParticlesEngineRight;
ParticleGeneratorExplosion* ParticlesEngineExpl;
ParticleGeneratorExplosion* ParticlesEngineShieldHit;
PostProcessor     * Effects;
ISoundEngine      * SoundEngine = createIrrKlangDevice();
GLfloat             ShakeTime = 0.0f;
TextRenderer      * Text;
GameShots         * AllPlayerShots;
Background        * GameBackgound;
EnemyObject       * Enemy;
GameEnemies       * AllGameEnemies;
MenuButton* ButtonContinue;
MenuButton* ButtonNew;
MenuButton* ButtonSave;
MenuButton* ButtonLoad;
MenuButton* ButtonHighScores;
std::vector <MenuButton*> AllMenuButtons;
std::vector<PowerUp*>   PowerUps;
int ActiveMenuButton;
int NextPowerUp;
Game::Game(GLuint width, GLuint height, GLuint scroll_speed)
        : State(GAME_MENU), Keys(), KeysProcessed(), Width(width), Height(height), Level(0), Shields(10), Score(0), ScrollSpeed(scroll_speed)
{

}

Game::~Game()
{
    delete Renderer;
    //delete Player;
    //delete Ball;
    delete Ship;
    delete Effects;
    delete Text;
    delete ParticlesEngineLeft;
    delete ParticlesEngineRight;
    SoundEngine->drop();
}

void Game::Init()
{
    // Load shaders
    ResourceManager::LoadShader("res/shaders/sprite.vert", "res/shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("res/shaders/particle.vert", "res/shaders/particle.frag", nullptr, "particle");
    ResourceManager::LoadShader("res/shaders/post_processing.vert", "res/shaders/post_processing.frag", nullptr, "postprocessing");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite")->Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite")->SetMatrix4("projection", projection);
    ResourceManager::GetShader("particle")->Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("particle")->SetMatrix4("projection", projection);
    // Load textures
    ResourceManager::LoadTexture("res/textures/background.jpg", GL_FALSE, "background");
    ResourceManager::LoadTexture("res/textures/awesomeface.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("res/textures/shot1.png", GL_TRUE, "shot1");
    ResourceManager::LoadTexture("res/textures/ship_shot0.png", GL_TRUE, "ship_shot0");
    ResourceManager::LoadTexture("res/textures/ship_shot1L.png", GL_TRUE, "ship_shot1L");
    ResourceManager::LoadTexture("res/textures/ship_shot1C.png", GL_TRUE, "ship_shot1C");
    ResourceManager::LoadTexture("res/textures/ship_shot1R.png", GL_TRUE, "ship_shot1R");
    ResourceManager::LoadTexture("res/textures/block.png", GL_FALSE, "block");
    ResourceManager::LoadTexture("res/textures/block_solid.png", GL_FALSE, "block_solid");
    ResourceManager::LoadTexture("res/textures/paddle_new.png", GL_TRUE, "paddle");
    ResourceManager::LoadTexture("res/textures/spaceship.png", GL_TRUE, "ship");
    ResourceManager::LoadTexture("res/textures/spaceshipR.png", GL_TRUE, "shipR");
    ResourceManager::LoadTexture("res/textures/spaceshipL.png", GL_TRUE, "shipL");
    ResourceManager::LoadTexture("res/textures/enemy.png", GL_TRUE, "enemy");
    ResourceManager::LoadTexture("res/textures/enemy1.png", GL_TRUE, "enemy1");
    ResourceManager::LoadTexture("res/textures/enemy2.png", GL_TRUE, "enemy2");
    ResourceManager::LoadTexture("res/textures/enemy3.png", GL_TRUE, "enemy3");
    ResourceManager::LoadTexture("res/textures/enemy4.png", GL_TRUE, "enemy4");
    ResourceManager::LoadTexture("res/textures/enemy5.png", GL_TRUE, "enemy5");
    ResourceManager::LoadTexture("res/textures/particle.png", GL_TRUE, "particle");
    ResourceManager::LoadTexture("res/textures/explosion.png", GL_TRUE, "explosion");
    ResourceManager::LoadTexture("res/textures/shield_hit.png", GL_TRUE, "shield_hit");
    ResourceManager::LoadTexture("res/textures/shield.png", GL_TRUE, "shield");
    ResourceManager::LoadTexture("res/textures/powerup_health.png", GL_TRUE, "powerup_health");
    ResourceManager::LoadTexture("res/textures/powerup_power.png", GL_TRUE, "powerup_power");
    ResourceManager::LoadTexture("res/textures/powerup_weapon1.png", GL_TRUE, "powerup_weapon1");
    ResourceManager::LoadTexture("res/textures/powerup_weapon2.png", GL_TRUE, "powerup_weapon2");
    ResourceManager::LoadTexture("res/textures/powerup_sticky.png", GL_TRUE, "powerup_sticky");
    ResourceManager::LoadTexture("res/textures/powerup_increase.png", GL_TRUE, "powerup_increase");
    ResourceManager::LoadTexture("res/textures/powerup_confuse.png", GL_TRUE, "powerup_confuse");
    ResourceManager::LoadTexture("res/textures/powerup_chaos.png", GL_TRUE, "powerup_chaos");
    ResourceManager::LoadTexture("res/textures/powerup_passthrough.png", GL_TRUE, "powerup_passthrough");
    ResourceManager::LoadTexture("res/textures/button.png", GL_TRUE, "button");
    ResourceManager::LoadTexture("res/textures/selection.png", GL_TRUE, "selection");
    ResourceManager::LoadTexture("res/textures/player_shields.png", GL_TRUE, "player_shields");

    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);
    Text = new TextRenderer(this->Width, this->Height);
    Text->Load("res/fonts/OCRAEXT.TTF", 24);
    // Set menu buttons
    ButtonContinue = new MenuButton(ResourceManager::GetShader("sprite"), ResourceManager::GetTexture("button"), ResourceManager::GetTexture("selection"), "Continue");
    ButtonNew = new MenuButton(ResourceManager::GetShader("sprite"), ResourceManager::GetTexture("button"), ResourceManager::GetTexture("selection"), "New Game");
    ButtonSave = new MenuButton(ResourceManager::GetShader("sprite"), ResourceManager::GetTexture("button"), ResourceManager::GetTexture("selection"), "Save");
    ButtonLoad = new MenuButton(ResourceManager::GetShader("sprite"), ResourceManager::GetTexture("button"), ResourceManager::GetTexture("selection"), "Load");
    ButtonHighScores = new MenuButton(ResourceManager::GetShader("sprite"), ResourceManager::GetTexture("button"), ResourceManager::GetTexture("selection"), "High Scores");
    AllMenuButtons.push_back(ButtonContinue);
    AllMenuButtons.push_back(ButtonNew);
    AllMenuButtons.push_back(ButtonSave);
    AllMenuButtons.push_back(ButtonLoad);
    AllMenuButtons.push_back(ButtonHighScores);
    ButtonNew->Activate();
    // Load levels
    GameLevel one;   one.Load  ("res/levels/one.lvl", this->Width, this->Height * 1.5);
    GameLevel two;   two.Load  ("res/levels/two.lvl", this->Width, this->Height * 1.5);
    GameLevel three; three.Load("res/levels/three.lvl", this->Width, this->Height * 1.5);
    GameLevel four;  four.Load ("res/levels/four.lvl", this->Width, this->Height * 1.5);
    // Load enemies    
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->Level = 0;
    // Configure menu buttons
    ButtonNew->ButtonAvailable = true;
    // Set active menu button
    ActiveMenuButton = 1;
    // Configure game objects
    glm::vec2 playerPos = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y*3);
    //Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));
    Ship = new ShipObject(playerPos, PLAYER_SIZE, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ship"));
    //Enemy = new EnemyObject(glm::vec2(this->Width/2, PLAYER_SIZE.y),30.0f, VELOCITY, ResourceManager::GetTexture("enemy"),1);
    glm::vec2 ballPos = glm::vec2(Ship->FiringPosition().x - BALL_RADIUS, Ship->FiringPosition().y - BALL_RADIUS);
    glm::vec2 ballPos_1 = glm::vec2(Ship->FiringPosition().x, Ship->FiringPosition().y - BALL_RADIUS);
    AllGameEnemies = new GameEnemies(&Ship->Position);
    AllPlayerShots = new GameShots();
    GameBackgound = new Background(glm::vec2(0, 0), ResourceManager::GetTexture("background"), Width, Height);
    //Shot = new ShotObject(Ship->FiringPosition(), 6.0f, 1, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
    AllGameEnemies->Load("res/levels/two.lvl", this->Width, this->Height * 0.5);
    //GameEnemies Wave1; Wave1.Load("res/levels/two.lvl", this->Width, this->Height * 0.5);
    // Audio
    SoundEngine->play2D("res/audio/breakout.mp3", GL_TRUE);
    //Set particle engines
    ParticlesEngineLeft = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 500);
    ParticlesEngineRight = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 500);
    NextPowerUp = 0;
}
void UpdateExplosionParticleEngines(std::vector <ParticleGeneratorExplosion*> explosionvector, GLfloat dt); //Explosion Particle engines update function
void Game::Update(GLfloat dt, GLfloat scroll_speed)
{
    // Update objects
    if (this->State == GAME_ACTIVE)
    {
        GameBackgound->Move(dt, scroll_speed, Height, glm::vec2(0.0f, 0.0f));
        AllPlayerShots->Move(dt, this->Width, this->Height, glm::vec2(Ship->FiringPosition().x - BALL_RADIUS, Ship->FiringPosition().y - BALL_RADIUS));
        AllGameEnemies->Move(dt, this->Width, this->Height);
        for (auto n : PowerUps)
        {
            n->Move(dt, 800);
        }
        this->DoCollisions();
    }
    ParticlesEngineLeft->Update(dt, *Ship, 2, glm::vec2(0.25f * Ship->Size.x, Ship->Size.y));
    ParticlesEngineRight->Update(dt, *Ship, 2, glm::vec2(0.68f * Ship->Size.x, Ship->Size.y));
    UpdateExplosionParticleEngines(ExplosionParticleEngines, dt);
    UpdateExplosionParticleEngines(ShieldHitParticleEngines, dt);
    // Update PowerUps
    this->UpdatePowerUps(dt);
    // Update Menu Buttons
    for (auto n : AllMenuButtons)
    {
        n->Deactivate();
    }
    AllMenuButtons[ActiveMenuButton]->Activate();
    // Reduce shake time
    if (ShakeTime > 0.0f)
    {
        ShakeTime -= dt;
        if (ShakeTime <= 0.0f)
            Effects->Shake = GL_FALSE;
    }
    // Check loss condition
    //if (Ball->Position.y >= this->Height) // Did ball reach bottom edge?
    //{
    //    --this->Lives;
    //    // Did the player lose all his lives? : Game over
    //    if (this->Lives == 0)
    //    {
    //        this->ResetLevel();
    //        this->State = GAME_MENU;
    //    }
    //    this->ResetPlayer();
    //}
    // Check win condition
    if (this->State == GAME_ACTIVE && this->Levels[this->Level].IsCompleted())
    {
        this->ResetLevel();
        this->ResetPlayer();
        Effects->Chaos = GL_TRUE;
        this->State = GAME_WIN;
    }
}


void Game::ProcessInput(GLfloat dt)
{
    if (this->State == GAME_MENU)
    {

        if ((this->Keys[GLFW_KEY_W] && !this->KeysProcessed[GLFW_KEY_W]) ||
           (this->Keys[GLFW_KEY_UP] && !this->KeysProcessed[GLFW_KEY_UP]))
        {
            if (!(ActiveMenuButton < 1))
            {
                ActiveMenuButton--;
            }

            this->KeysProcessed[GLFW_KEY_W] = GL_TRUE;
            this->KeysProcessed[GLFW_KEY_UP] = GL_TRUE;
        }
        if ((this->Keys[GLFW_KEY_S] && !this->KeysProcessed[GLFW_KEY_S]) ||
           (this->Keys[GLFW_KEY_DOWN] && !this->KeysProcessed[GLFW_KEY_DOWN]))
        {
            if (!(ActiveMenuButton >3))
            {
                ActiveMenuButton++;
            }
            this->KeysProcessed[GLFW_KEY_S] = GL_TRUE;
            this->KeysProcessed[GLFW_KEY_DOWN] = GL_TRUE;
        }
        if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
        {
            AllMenuButtons[ActiveMenuButton]->Press();
            if (AllMenuButtons[1]->ButtonPressed)
            {
                this->State = GAME_ACTIVE;
                AllMenuButtons[1]->UnPress();
            }
            this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;          
        }

    }
    if (this->State == GAME_WIN)
    {
        if (this->Keys[GLFW_KEY_ENTER])
        {
            this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
            Effects->Chaos = GL_FALSE;
            this->State = GAME_MENU;
        }
    }
    if (this->State == GAME_ACTIVE)
    {
        GLfloat velocity = PLAYER_VELOCITY * dt;
        // Move playerboard
        if (this->Keys[GLFW_KEY_A] || this->Keys[GLFW_KEY_LEFT])
        {
            Ship->Sprite = ResourceManager::GetTexture("shipL");
            if (Ship->Position.x >= -Ship->Size.x/3)
            {
                Ship->Position.x -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_D] || this->Keys[GLFW_KEY_RIGHT])
        {
            Ship->Sprite = ResourceManager::GetTexture("shipR");
            if (Ship->Position.x <= this->Width - Ship->Size.x/1.5f)
            {
                Ship->Position.x += velocity;
            }
        }
        if (!(this->Keys[GLFW_KEY_A] || this->Keys[GLFW_KEY_LEFT]|| this->Keys[GLFW_KEY_D] || this->Keys[GLFW_KEY_RIGHT])) Ship->Sprite = ResourceManager::GetTexture("ship");
        if (this->Keys[GLFW_KEY_W] || this->Keys[GLFW_KEY_UP])
        {
            if (Ship->Position.y >= 0)
            {
                Ship->Position.y -= velocity;
            }
        }
        if (this->Keys[GLFW_KEY_S] || this->Keys[GLFW_KEY_DOWN])
        {
            if (Ship->Position.y <= this->Height - Ship->Size.y)
            {
                Ship->Position.y += velocity;
            }
        }
        if (this->Keys[GLFW_KEY_SPACE] && !this->KeysProcessed[GLFW_KEY_SPACE])
        {     
            if (Ship->WeaponType == 0) //TODO create struct for NewShot initialization
            {
                if (Ship->WeaponPower >= 0)
                {
                    AllPlayerShots->NewShot(Ship->FiringPosition() - glm::vec2(BALL_RADIUS * 4, 0.0f), BALL_RADIUS, 1, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ship_shot0"));
                    AllPlayerShots->NewShot(Ship->FiringPosition() + glm::vec2(BALL_RADIUS * 2, 0.0f), BALL_RADIUS, 1, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ship_shot0"));
                }
                if (Ship->WeaponPower == 1)
                {
                    AllPlayerShots->NewShot(Ship->FiringPosition() - glm::vec2(BALL_RADIUS, 0.0f), BALL_RADIUS, 1, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ship_shot0"));

                }
                if (Ship->WeaponPower >= 2)
                {
                    AllPlayerShots->NewShot(Ship->FiringPosition() - glm::vec2(BALL_RADIUS * 2, 0.0f), BALL_RADIUS, 1, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ship_shot0"));
                    AllPlayerShots->NewShot(Ship->FiringPosition(), BALL_RADIUS, 1, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ship_shot0"));
                }
            }
            if (Ship->WeaponType == 1)
            {
                if (Ship->WeaponPower == 0)
                {
                    AllPlayerShots->NewShot(Ship->FiringPosition() - glm::vec2(BALL_RADIUS * 4, 0.0f),
                        BALL_RADIUS, 1, glm::vec2(INITIAL_BALL_VELOCITY.y * 0.5f, INITIAL_BALL_VELOCITY.y * 0.7f), ResourceManager::GetTexture("ship_shot1L"));
                    AllPlayerShots->NewShot(Ship->FiringPosition() - glm::vec2(BALL_RADIUS, 0.0f), BALL_RADIUS, 1, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ship_shot1C"));
                    AllPlayerShots->NewShot(Ship->FiringPosition() + glm::vec2(BALL_RADIUS * 2, 0.0f), 
                        BALL_RADIUS, 1, glm::vec2(-INITIAL_BALL_VELOCITY.y * 0.5f, INITIAL_BALL_VELOCITY.y * 0.7f), ResourceManager::GetTexture("ship_shot1R"));
                }
                if (Ship->WeaponPower == 1)
                {
                    AllPlayerShots->NewShot(Ship->FiringPosition() - glm::vec2(BALL_RADIUS * 4, 0.0f),
                        BALL_RADIUS, 1, glm::vec2(INITIAL_BALL_VELOCITY.y * 0.5f, INITIAL_BALL_VELOCITY.y * 0.7f), ResourceManager::GetTexture("ship_shot1L"));
                    AllPlayerShots->NewShot(Ship->FiringPosition() - glm::vec2(BALL_RADIUS * 2, 0.0f), BALL_RADIUS, 1, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ship_shot1C"));
                    AllPlayerShots->NewShot(Ship->FiringPosition() + glm::vec2(BALL_RADIUS * 1, 0.0f), BALL_RADIUS, 1, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ship_shot1C"));
                    AllPlayerShots->NewShot(Ship->FiringPosition() + glm::vec2(BALL_RADIUS * 2, 0.0f),
                        BALL_RADIUS, 1, glm::vec2(-INITIAL_BALL_VELOCITY.y * 0.5f, INITIAL_BALL_VELOCITY.y * 0.7f), ResourceManager::GetTexture("ship_shot1R"));
                }
                if (Ship->WeaponPower >= 2)
                {
                    AllPlayerShots->NewShot(Ship->FiringPosition() - glm::vec2(BALL_RADIUS * 4, 0.0f),
                        BALL_RADIUS, 1, glm::vec2(INITIAL_BALL_VELOCITY.y * 0.5f, INITIAL_BALL_VELOCITY.y * 0.7f), ResourceManager::GetTexture("ship_shot1L"));
                    AllPlayerShots->NewShot(Ship->FiringPosition() - glm::vec2(BALL_RADIUS * 7, 0.0f),
                        BALL_RADIUS, 1, glm::vec2(INITIAL_BALL_VELOCITY.y * 0.5f, INITIAL_BALL_VELOCITY.y * 0.7f), ResourceManager::GetTexture("ship_shot1L"));
                    AllPlayerShots->NewShot(Ship->FiringPosition() - glm::vec2(BALL_RADIUS * 2, 0.0f), BALL_RADIUS, 1, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ship_shot1C"));
                    AllPlayerShots->NewShot(Ship->FiringPosition() + glm::vec2(BALL_RADIUS * 1, 0.0f), BALL_RADIUS, 1, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ship_shot1C"));
                    AllPlayerShots->NewShot(Ship->FiringPosition() + glm::vec2(BALL_RADIUS * 2, 0.0f),
                        BALL_RADIUS, 1, glm::vec2(-INITIAL_BALL_VELOCITY.y * 0.5f, INITIAL_BALL_VELOCITY.y * 0.7f), ResourceManager::GetTexture("ship_shot1R"));
                    AllPlayerShots->NewShot(Ship->FiringPosition() + glm::vec2(BALL_RADIUS * 5, 0.0f),
                        BALL_RADIUS, 1, glm::vec2(-INITIAL_BALL_VELOCITY.y * 0.5f, INITIAL_BALL_VELOCITY.y * 0.7f), ResourceManager::GetTexture("ship_shot1R"));
                }
            }
            SoundEngine->play2D("res/audio/laser.wav", GL_FALSE);
            this->KeysProcessed[GLFW_KEY_SPACE] = GL_TRUE;
        }
    }
}

void Game::Render()
{
    if (this->State == GAME_ACTIVE || State == GAME_LOSE)//|| this->State == GAME_MENU || this->State == GAME_WIN)
    {
        // Begin rendering to postprocessing quad
        Effects->BeginRender();
            // Draw background
            GameBackgound->Draw(*Renderer);
            // Draw player engines
            ParticlesEngineLeft->Draw();
            ParticlesEngineRight->Draw();
            // Draw all enemy ships in a wave
            AllGameEnemies->Draw(*Renderer);
            // Draw player
            Ship->Draw(*Renderer);
            // Draw PowerUps
            //for (PowerUp &powerUp : this->PowerUps)
            //    if (!powerUp.Destroyed)
            //        powerUp.Draw(*Renderer);

            for (auto n : PowerUps)
            {
                n->Draw(*Renderer);
            }
            //draw all explosions
            if (ExplosionParticleEngines.size() > 0) 
            {
                for (auto n : ExplosionParticleEngines)
                {
                    n->Draw();
                }
            }
            //draw all shield hits
            if (ShieldHitParticleEngines.size() > 0) 
            {
                for (auto n : ShieldHitParticleEngines)
                {
                    n->Draw();
                }
            }

            //draw all player shots
            AllPlayerShots->Draw(*Renderer);
         // End rendering to postprocessing quad
        Effects->EndRender();
        // Render postprocessing quad
        Effects->Render(glfwGetTime());
        // Render text (don't include in postprocessing)
        std::stringstream ss; ss << this->Score;
        Text->RenderText("Score:" + ss.str(), 5.0f, 5.0f, 1.0f);
        Text->RenderText("Shields:", 172.0f, 5.0f, 1.0f);
        for (int i = 0; i < Shields; i++) Renderer->DrawSprite(ResourceManager::GetTexture("player_shields"), glm::vec2(295.0f + i * 45.0f, 10.0f), glm::vec2(40.0f, 10.0f));
        //TODO  remove std::stringstream ss1; ss1 << this->Shields;
        //      Text->RenderText("Shields:" + ss1.str(), 170.0f, 50.0f, 1.0f);
    }
    if (this->State == GAME_MENU)
    {
        const glm::vec2 MenuPositions[] = {
        glm::vec2(270.0f, 300.0f),
        glm::vec2(270.0f, 350.0f),
        glm::vec2(270.0f, 400.0f),
        glm::vec2(270.0f, 450.0f),
        glm::vec2(270.0f, 500.0f)
        };
        const glm::vec2 ButtonSize = glm::vec2(260.0f, 50.0f);

        //Renderer->DrawSprite(ResourceManager::GetTexture("enemy1"), glm::vec2(this->Width / 2, this->Height / 2 + 40.0f));
        //Text->RenderText("Press ENTER to start", 250.0f, this->Height / 2, 1.0f);
        //Text->RenderText("Press W or S to select level", 245.0f, this->Height / 2 + 20.0f, 0.75f);
        //ButtonContinue->Draw(*Renderer, *Text, MenuPositions[0], ButtonSize);
        //ButtonNew->ButtonActive = true;
        //ButtonNew->ButtonAvailable = true;

        for (auto it=AllMenuButtons.begin(); it!=AllMenuButtons.end();it++)
        {
            int index = it - AllMenuButtons.begin();
            (*it)->Draw(*Renderer, *Text, MenuPositions[index], ButtonSize);
        }
    }
    if (this->State == GAME_WIN)
    {
        Text->RenderText("You WON!!!", 320.0f, this->Height / 2 - 20.0f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        Text->RenderText("Press ENTER to retry or ESC to quit", 130.0f, this->Height / 2, 1.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    }
}

void Game::ResetLevel()
{
    if (this->Level == 0)this->Levels[0].Load("res/levels/one.lvl", this->Width, this->Height * 0.5f);
    else if (this->Level == 1)
        this->Levels[1].Load("res/levels/two.lvl", this->Width, this->Height * 0.5f);
    else if (this->Level == 2)
        this->Levels[2].Load("res/levels/three.lvl", this->Width, this->Height * 0.5f);
    else if (this->Level == 3)
        this->Levels[3].Load("res/levels/four.lvl", this->Width, this->Height * 0.5f);

    this->Shields = 3;
}

void Game::ResetPlayer()
{
    // Reset player/ball stats
    Ship->Size = PLAYER_SIZE;
    Ship->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    // Also disable all active powerups
    Effects->Chaos = Effects->Confuse = GL_FALSE;
    Ship->Color = glm::vec3(1.0f);
}

// PowerUps
GLboolean IsOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type);

void Game::UpdatePowerUps(GLfloat dt)
{
    //for (PowerUp &powerUp : this->PowerUps)
    //{
    //    powerUp.Position += powerUp.Velocity * dt;
    //    if (powerUp.Activated)
    //    {
    //        powerUp.Duration -= dt;

    //        if (powerUp.Duration <= 0.0f)
    //        {
    //            // Remove powerup from list (will later be removed)
    //            powerUp.Activated = GL_FALSE;
    //            // Deactivate effects
    //            if (powerUp.Type == "sticky")
    //            {
    //                if (!IsOtherPowerUpActive(this->PowerUps, "sticky"))
    //                {	// Only reset if no other PowerUp of type sticky is active
    //                    Ship->Color = glm::vec3(1.0f);
    //                }
    //            }
    //           
    //            else if (powerUp.Type == "confuse")
    //            {
    //                if (!IsOtherPowerUpActive(this->PowerUps, "confuse"))
    //                {	// Only reset if no other PowerUp of type confuse is active
    //                    Effects->Confuse = GL_FALSE;
    //                }
    //            }
    //            else if (powerUp.Type == "chaos")
    //            {
    //                if (!IsOtherPowerUpActive(this->PowerUps, "chaos"))
    //                {	// Only reset if no other PowerUp of type chaos is active
    //                    Effects->Chaos = GL_FALSE;
    //                }
    //            }
    //        }
    //    }
    //}
    //// Remove all PowerUps from vector that are destroyed AND !activated (thus either off the map or finished)
    //// Note we use a lambda expression to remove each PowerUp which is destroyed and not activated
    //this->PowerUps.erase(std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
    //                                    [](const PowerUp &powerUp) { return powerUp.Destroyed && !powerUp.Activated; }
    //), this->PowerUps.end());
}

GLboolean ShouldSpawn(GLuint chance)
{
    GLuint random = rand() % chance;
    return random == 0;
}
void Game::SpawnPowerUps(GameObject &block)
{
    //if (ShouldSpawn(75)) // 1 in 75 chance
    //    this->PowerUps.push_back(PowerUp("speed", glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed")));
    //if (ShouldSpawn(75))
    //    this->PowerUps.push_back(PowerUp("sticky", glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky")));
    //if (ShouldSpawn(75))
    //    this->PowerUps.push_back(PowerUp("pass-through", glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough")));
    //if (ShouldSpawn(75))
    //    this->PowerUps.push_back(PowerUp("pad-size-increase", glm::vec3(1.0f, 0.6f, 0.4), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase")));
    //if (ShouldSpawn(15)) // Negative powerups should spawn more often
    //    this->PowerUps.push_back(PowerUp("confuse", glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse")));
    //if (ShouldSpawn(15))
    //    this->PowerUps.push_back(PowerUp("chaos", glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos")));
}

void ActivatePowerUp(PowerUp &powerUp)
{
//    // Initiate a powerup based type of powerup
//    if (powerUp.Type == "pad-size-increase")
//    {
//        Ship->Size.x += 50;
//    }
//    else if (powerUp.Type == "confuse")
//    {
//        if (!Effects->Chaos)
//            Effects->Confuse = GL_TRUE; // Only activate if chaos wasn't already active
//    }
//    else if (powerUp.Type == "chaos")
//    {
//        if (!Effects->Confuse)
//            Effects->Chaos = GL_TRUE;
//    }
}

GLboolean IsOtherPowerUpActive(std::vector<PowerUp> &powerUps, std::string type)
{
    //// Check if another PowerUp of the same type is still active
    //// in which case we don't disable its effect (yet)
    //for (const PowerUp &powerUp : powerUps)
    //{
    //    if (powerUp.Activated)
    //        if (powerUp.Type == type)
    //            return GL_TRUE;
    //}
    return GL_FALSE;
}

// Collision detection
GLboolean CheckCollisionShotEnemy(ShotObject &one, EnemyObject &two);
GLboolean CheckCollisionShipEnemy(ShipObject& one, EnemyObject& two);
GLboolean CheckCollisionShipShot(ShipObject& one, ShotObject& two);
GLboolean CheckCollisionShipPowerUp(ShipObject& one, PowerUp& two);

Direction VectorDirection(glm::vec2 closest);

void Game::DoCollisions()
{
    //
    //for (GameObject &box : this->Levels[this->Level].Bricks)
    //{
    //    if (!box.Destroyed)
    //    {
    //        Collision collision = CheckCollision(*Ball, box);
    //        if (std::get<0>(collision)) // If collision is true
    //        {
    //            // Destroy block if not solid
    //            if (!box.IsSolid)
    //            {
    //                box.Destroyed = GL_TRUE;
    //                this->SpawnPowerUps(box);
    //                SoundEngine->play2D("res/audio/bleep.mp3", GL_FALSE);
    //            }
    //            else
    //            {   // if block is solid, enable shake effect
    //                ShakeTime = 0.05f;
    //                Effects->Shake = GL_TRUE;
    //                SoundEngine->play2D("res/audio/solid.wav", GL_FALSE);
    //            }
    //            // Collision resolution
    //            Direction dir = std::get<1>(collision);
    //            glm::vec2 diff_vector = std::get<2>(collision);
    //            if (!(Ball->PassThrough && !box.IsSolid)) // don't do collision resolution on non-solid bricks if pass-through activated
    //            {
    //                if (dir == LEFT || dir == RIGHT) // Horizontal collision
    //                {
    //                    Ball->Velocity.x = -Ball->Velocity.x; // Reverse horizontal velocity
    //                    // Relocate
    //                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
    //                    if (dir == LEFT)
    //                        Ball->Position.x += penetration; // Move ball to right
    //                    else
    //                        Ball->Position.x -= penetration; // Move ball to left;
    //                }
    //                else // Vertical collision
    //                {
    //                    Ball->Velocity.y = -Ball->Velocity.y; // Reverse vertical velocity
    //                    // Relocate
    //                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
    //                    if (dir == UP)
    //                        Ball->Position.y -= penetration; // Move ball bback up
    //                    else
    //                        Ball->Position.y += penetration; // Move ball back down
    //                }
    //            }
    //        }
    //    }
    //}

    //// Also check collisions on PowerUps and if so, activate them
    //for (PowerUp &powerUp : this->PowerUps)
    //{
    //    if (!powerUp.Destroyed)
    //    {
    //        // First check if powerup passed bottom edge, if so: keep as inactive and destroy
    //        if (powerUp.Position.y >= this->Height)
    //            powerUp.Destroyed = GL_TRUE;

    //        if (CheckCollision(*Ship, powerUp))
    //        {	// Collided with player, now activate powerup
    //            ActivatePowerUp(powerUp);
    //            powerUp.Destroyed = GL_TRUE;
    //            powerUp.Activated = GL_TRUE;
    //            SoundEngine->play2D("res/audio/powerup.wav", GL_FALSE);
    //        }
    //    }
    //}

    // And finally check collisions for player pad (unless stuck)
    //Collision result = CheckCollision(*Ball, *Ship);
    //if (!Ball->Stuck && std::get<0>(result))
    //{
    //    // Check where it hit the board, and change velocity based on where it hit the board
    //    GLfloat centerBoard = Ship->Position.x + Ship->Size.x / 2;
    //    GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
    //    GLfloat percentage = distance / (Ship->Size.x / 2);
    //    // Then move accordingly
    //    GLfloat strength = 2.0f;
    //    glm::vec2 oldVelocity = Ball->Velocity;
    //    Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
    //    //Ball->Velocity.y = -Ball->Velocity.y;
    //    Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
    //    // Fix sticky paddle
    //    Ball->Velocity.y = -1 * abs(Ball->Velocity.y);

    //    // If Sticky powerup is activated, also stick ball to paddle once new velocity vectors were calculated
    //    Ball->Stuck = Ball->Sticky;

    //    SoundEngine->play2D("res/audio/bleep.wav", GL_FALSE);
    //}

    //Collisions between player shots and enemies
    for (auto EnemyIterator = AllGameEnemies->Enemies.begin(); EnemyIterator != AllGameEnemies->Enemies.end(); EnemyIterator++)
    {
        for (auto ShotIterator = AllPlayerShots->Shots.begin(); ShotIterator != AllPlayerShots->Shots.end(); ShotIterator++)
        {
            if (CheckCollisionShotEnemy(*(*ShotIterator), *(*EnemyIterator)))
            {
                int temp = (*ShotIterator)->Power;
                (*ShotIterator)->Power -= (*EnemyIterator)->Strenght;
                (*EnemyIterator)->Strenght -= temp;
                if ((*EnemyIterator)->Strenght > 0)
                {
                    SoundEngine->play2D("res/audio/shieldhit.wav", GL_FALSE); //if enemy has shields
                    ShieldHitParticleEngines.push_back(new ParticleGeneratorExplosion(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("shield_hit"), 500,
                        *(*ShotIterator), 2, glm::vec2(0, 0), glm::vec4(0.0f, 0.5f, 1.0f, 1.0f), 0.4f));

                }
                else
                {
                    ExplosionParticleEngines.push_back(new ParticleGeneratorExplosion(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("explosion"), 500,
                        *(*EnemyIterator), 2, (*EnemyIterator)->Size / 2.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), 0.7f));
                    Score += (*EnemyIterator)->ScorePoints;
                    if ((*EnemyIterator)->Type == 5) // drop powerup if enemy detroyed by shot
                    {
                        if (NextPowerUp % 4 == 0) //TODO create a variable to hold the texture and remove ifs
                        {
                            PowerUps.push_back(new PowerUp(NextPowerUp % 4, glm::vec3(1.0f, 1.0f, 1.0f), 
                                (*EnemyIterator)->Position, glm::vec2(0.0f, 70.0f), POWER_UP_SIZE, ResourceManager::GetTexture("powerup_health")));
                        }
                        if (NextPowerUp % 4 == 1)
                        {
                            PowerUps.push_back(new PowerUp(NextPowerUp % 4, glm::vec3(1.0f, 1.0f, 1.0f), 
                                (*EnemyIterator)->Position, glm::vec2(0.0f, 70.0f), POWER_UP_SIZE, ResourceManager::GetTexture("powerup_power")));
                        }
                        if (NextPowerUp % 4 == 2)
                        {
                            PowerUps.push_back(new PowerUp(NextPowerUp % 4, glm::vec3(1.0f, 1.0f, 1.0f), 
                                (*EnemyIterator)->Position, glm::vec2(0.0f, 70.0f), POWER_UP_SIZE, ResourceManager::GetTexture("powerup_weapon1")));
                        }
                        if (NextPowerUp % 4 == 3)
                        {
                            PowerUps.push_back(new PowerUp(NextPowerUp % 4, glm::vec3(1.0f, 1.0f, 1.0f), 
                                (*EnemyIterator)->Position, glm::vec2(0.0f, 70.0f), POWER_UP_SIZE, ResourceManager::GetTexture("powerup_weapon2")));
                        }
                        NextPowerUp++;
                    }
                }
            }
        }
        AllPlayerShots->Clean();
    }
    if (AllGameEnemies->Clean()) SoundEngine->play2D("res/audio/boom.wav", GL_FALSE);

    //Collisions between player and enemies
    for (auto EnemyIterator = AllGameEnemies->Enemies.begin(); EnemyIterator != AllGameEnemies->Enemies.end(); EnemyIterator++)
    {
        if (CheckCollisionShipEnemy(*Ship, *(*EnemyIterator)))
        {
            (*EnemyIterator)->Strenght = 0;
            if (Shields > 0)
            {
                Shields--;
            }
            else 
            {
                State = GAME_LOSE;
            }
            ExplosionParticleEngines.push_back(new ParticleGeneratorExplosion(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("explosion"), 500,
                *(*EnemyIterator), 2, (*EnemyIterator)->Size / 2.0f, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), 0.7f));
            Score += (*EnemyIterator)->ScorePoints;
            SoundEngine->play2D("res/audio/boom.wav", GL_FALSE);
        }
    }

    //Collisions between player and enemy shots
    for (auto EnemyShotIterator = AllGameEnemies->Shots.begin(); EnemyShotIterator != AllGameEnemies->Shots.end(); EnemyShotIterator++)
    {
        if (CheckCollisionShipShot(*Ship, *(*EnemyShotIterator)))
        {
            if (Shields > 0)
            {
                Shields--;
                (*EnemyShotIterator)->Power = 0;
                SoundEngine->play2D("res/audio/shieldhit.wav", GL_FALSE); //if ship has shields
                ShieldHitParticleEngines.push_back(new ParticleGeneratorExplosion(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("shield_hit"), 500,
                    *(*EnemyShotIterator), 2, glm::vec2(0, 0), glm::vec4(0.0f, 0.5f, 1.0f, 1.0f), 0.4f));
            }
            else
            {
                State = GAME_LOSE;
            }
        }
    }
    //Collisions between player and powerups
    for (auto PowerUpIterator = PowerUps.begin(); PowerUpIterator != PowerUps.end();)
    {
        if (CheckCollisionShipPowerUp(*Ship, *(*PowerUpIterator)))
        {
            switch ((*PowerUpIterator)->Type)
            {
            case 0:
                if (Shields > 6) { Shields = 10; }
                else { Shields = Shields + 3; }
                break;
            case 1:
                Ship->WeaponPower++;
                break;
            case 2:
                Ship->WeaponType = 0;
                break;
            case 3:
                Ship->WeaponType = 1;
                break;
            }
            PowerUps.erase(PowerUpIterator);
            PowerUpIterator = PowerUps.end();
            SoundEngine->play2D("res/audio/power_up.ogg", GL_FALSE);
        }
        else { PowerUpIterator++; }
    }
    

}



GLboolean CheckCollisionShotEnemy(ShotObject& shot, EnemyObject& enemy) // AABB - AABB collision
{
    // Collision x-axis?
    bool collisionX = shot.Position.x + shot.Size.x >= enemy.Position.x &&
        enemy.Position.x + enemy.Size.x >= shot.Position.x;
    // Collision y-axis?
    bool collisionY = shot.Position.y + shot.Size.y >= enemy.Position.y &&
        enemy.Position.y + enemy.Size.y >= shot.Position.y;
    // Collision only if on both axes
    GLboolean a = collisionX && collisionY;
    return a;// collisionX&& collisionY;
}

GLboolean CheckCollisionShipEnemy(ShipObject& ship, EnemyObject& enemy) // AABB - AABB collision
{
    // Collision x-axis?
    bool collisionX = ship.Position.x + ship.Size.x >= enemy.Position.x &&
        enemy.Position.x + enemy.Size.x >= ship.Position.x;
    // Collision y-axis?
    bool collisionY = ship.Position.y + ship.Size.y >= enemy.Position.y &&
        enemy.Position.y + enemy.Size.y >= ship.Position.y;
    // Collision only if on both axes
    GLboolean a = collisionX && collisionY;
    return a;// collisionX&& collisionY;
}

GLboolean CheckCollisionShipShot(ShipObject& ship, ShotObject& shot) // AABB - AABB collision
{
    // Collision x-axis?
    bool collisionX = ship.Position.x + ship.Size.x >= shot.Position.x &&
        shot.Position.x + shot.Size.x >= ship.Position.x;
    // Collision y-axis?
    bool collisionY = ship.Position.y + ship.Size.y >= shot.Position.y &&
        shot.Position.y + shot.Size.y >= ship.Position.y;
    // Collision only if on both axes
    GLboolean a = collisionX && collisionY;
    return a;// collisionX&& collisionY;
}

GLboolean CheckCollisionShipPowerUp(ShipObject& ship, PowerUp& power_up) // AABB - AABB collision
{
    // Collision x-axis?
    bool collisionX = ship.Position.x + ship.Size.x >= power_up.Position.x &&
        power_up.Position.x + power_up.Size.x >= ship.Position.x;
    // Collision y-axis?
    bool collisionY = ship.Position.y + ship.Size.y >= power_up.Position.y &&
        power_up.Position.y + power_up.Size.y >= ship.Position.y;
    // Collision only if on both axes
    GLboolean a = collisionX && collisionY;
    return a;// collisionX&& collisionY;
}

//GLboolean CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
//{
//    // Collision x-axis?
//    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
//                      two.Position.x + two.Size.x >= one.Position.x;
//    // Collision y-axis?
//    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
//                      two.Position.y + two.Size.y >= one.Position.y;
//    // Collision only if on both axes
//    return collisionX && collisionY;
//}

//Collision CheckCollision(BallObject &one, GameObject &two) // AABB - Circle collision
//{
//    // Get center point circle first
//    glm::vec2 center(one.Position + one.Radius);
//    // Calculate AABB info (center, half-extents)
//    glm::vec2 aabb_half_extents(two.Size.x / 2, two.Size.y / 2);
//    glm::vec2 aabb_center(two.Position.x + aabb_half_extents.x, two.Position.y + aabb_half_extents.y);
//    // Get difference vector between both centers
//    glm::vec2 difference = center - aabb_center;
//    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
//    // Now that we know the the clamped values, add this to AABB_center and we get the value of box closest to circle
//    glm::vec2 closest = aabb_center + clamped;
//    // Now retrieve vector between center circle and closest point AABB and check if length < radius
//    difference = closest - center;
//
//    if (glm::length(difference) < one.Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
//        return std::make_tuple(GL_TRUE, VectorDirection(difference), difference);
//    else
//        return std::make_tuple(GL_FALSE, UP, glm::vec2(0, 0));
//}

// Calculates which direction a vector is facing (N,E,S or W)
Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
            glm::vec2(0.0f, 1.0f),	// up
            glm::vec2(1.0f, 0.0f),	// right
            glm::vec2(0.0f, -1.0f),	// down
            glm::vec2(-1.0f, 0.0f)	// left
    };
    GLfloat max = 0.0f;
    GLuint best_match = -1;
    for (GLuint i = 0; i < 4; i++)
    {
        GLfloat dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}
void UpdateExplosionParticleEngines(std::vector <ParticleGeneratorExplosion*> explosionvector, GLfloat dt)
{
    explosionvector.erase(std::remove_if(explosionvector.begin(), explosionvector.end(), [](ParticleGeneratorExplosion* generator)->bool {return generator->generator_life < 0; }), explosionvector.end());

    if (explosionvector.size() > 0)
    {
        for (auto n : explosionvector)
        {
            n->Update(dt);
        }
    }
}