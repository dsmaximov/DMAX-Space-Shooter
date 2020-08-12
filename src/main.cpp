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
#include <iostream>
#include <windows.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "framework/core/game.h"
#include "framework/core/resource_manager.h"


// GLFW function declerations
void key_callback(GLFWwindow* window, GLint key, int scancode, int action, int mode);

// The Width of the screen
const GLuint SCREEN_WIDTH = 800;
// The height of the screen
const GLuint SCREEN_HEIGHT = 800;
// The scrolling speed of background
const GLuint SCROLL_SPEED = 70;

Game DMAX_Shooter(SCREEN_WIDTH, SCREEN_HEIGHT, SCROLL_SPEED);

int main(int argc, char *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DMAX_Shooter", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    // OpenGL configuration
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize game
    DMAX_Shooter.Init();

    // DeltaTime variables
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        //deltaTime = 0.001f;
        // Manage user input
        DMAX_Shooter.ProcessInput(deltaTime);
        // Update Game state
        DMAX_Shooter.Update(deltaTime, SCROLL_SPEED, glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));

        // Render
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        DMAX_Shooter.Render();

        glfwSwapBuffers(window);
    }

    // Delete all resources as loaded using the resource manager
    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, GLint key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        if (DMAX_Shooter.State == GAME_MAIN_MENU) glfwSetWindowShouldClose(window, GL_TRUE);
  // TODO delete     if (Breakout.State == GAME_ACTIVE || Breakout.State == GAME_LOSE || Breakout.State == GAME_HIGHSCORE) Breakout.State = GAME_MENU;
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            DMAX_Shooter.Keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
        {
            DMAX_Shooter.Keys[key] = GL_FALSE;
            DMAX_Shooter.KeysProcessed[key] = GL_FALSE;
        }
    }
    DMAX_Shooter.KeyCode = key;
    DMAX_Shooter.KeyAction = action;
}