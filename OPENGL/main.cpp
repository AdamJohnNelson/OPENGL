#include <stdio.h>
#include <chrono>
#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Controller.h"
#include "ShaderManager.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void glfw_window_size_callback(GLFWwindow* window, int width, int height);

ShaderManager ShaderControls;
Controller Controls;

int WindowWidth = 1080;
int WindowHeight = 720;

double CurrentTime = 0;
double PreviousTime = 0;

float translate[16] =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float scale[16] =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

float Triangle[9] =
{
    -0.5f, -0.5f, 1.0f,
     0.0f,  0.5f, 1.0f,
     0.5f, -0.5f, 1.0f
};

float Square[12] =
{
  -0.05f, -0.05f, 1.0f,
  -0.05f,  0.05f, 1.0f,
   0.05f, -0.05f, 1.0f,
   0.05f,  0.05f, 1.0f
};

float Cube[24] =
{
  -0.05f, -0.05f, 1.0f,
  -0.05f,  0.05f, 1.0f,
   0.05f, -0.05f, 1.0f,
   0.05f,  0.05f, 1.0f,

  -0.05f, -0.05f, 1.5f,
  -0.05f,  0.05f, 1.5f,
   0.05f, -0.05f, 1.5f,
   0.05f,  0.05f, 1.5f
};

unsigned int TriangleIndices[3] =
{
    0,1,2
};

unsigned int SquareIndices[6] =
{
    0, 1, 2,
    2, 1, 3
};

unsigned int CubeIndices[36] =
{
    0,1,2, //front face
    2,1,3,
    
    3,2,7, //right face
    7,2,6,

    6,7,4, //back face
    4,5,6,

    4,1,5, //left face
    4,0,1,

    1,5,2, //top face
    2,5,6,

    0,4,3, //bottom face
    3,4,7
};

int main(int argc, char* argv[])
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(WindowWidth, WindowHeight, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetWindowSizeCallback(window, glfw_window_size_callback);
    glfwMakeContextCurrent(window);

    /* Initialize GLEW*/
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    else
    {
        std::cout << glGetString(GL_VERSION) << std::endl;
    }

    unsigned int buffer = 0;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), Cube, GL_STATIC_DRAW);

    unsigned int vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), SquareIndices, GL_STATIC_DRAW);

    GLuint ShaderProgram = glCreateProgram();
    GLuint VertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragShader = glCreateShader(GL_FRAGMENT_SHADER);
    ShaderControls.CompileShader(VertShader, "test_vs.glsl", GL_VERTEX_SHADER);
    ShaderControls.CompileShader(FragShader, "test_fs.glsl", GL_FRAGMENT_SHADER);
    ShaderControls.AttachShader(ShaderProgram, VertShader);
    ShaderControls.AttachShader(ShaderProgram, FragShader);
    ShaderControls.LinkProgram(ShaderProgram);
    ShaderControls.UseProgram(ShaderProgram);

    GLint Translate = glGetUniformLocation(ShaderProgram, "u_Translate");
    glUniformMatrix4fv(Translate, 1, GL_TRUE, &translate[0]);
    GLuint Scale = glGetUniformLocation(ShaderProgram, "u_Scale");
    glUniformMatrix4fv(Scale, 1, GL_TRUE, &scale[0]);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        /* Render here */
        std::chrono::steady_clock::time_point Start = std::chrono::steady_clock::now();
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, WindowWidth, WindowHeight);
        Controls.SetDirectionVector();
        Controls.SetScaleVector();
        translate[3] = translate[3] + Controls.DirectionVector.x;
        translate[7] = translate[7] + Controls.DirectionVector.y;
        scale[0] = scale[0] + Controls.ScaleVector.x;
        scale[5] = scale[5] + Controls.ScaleVector.y;
        glUniformMatrix4fv(Translate, 1, GL_TRUE, translate);
        glUniformMatrix4fv(Scale, 1, GL_TRUE, scale);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        std::chrono::steady_clock::time_point End = std::chrono::steady_clock::now();
        std::chrono::steady_clock::duration RenderTime = End - Start;
        //std::cout << RenderTime.count() << std::endl;
       
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */        
        glfwGetCursorPos(window, &Controls.CursorX, &Controls.CursorY);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_W:
    {
        switch (action)
        {
        case GLFW_PRESS:
            Controls.WKeyState = true;
            break;

        case GLFW_REPEAT:
            break;

        case GLFW_RELEASE:
            Controls.WKeyState = false;
            break;
        }
    }
    break;

    case GLFW_KEY_S:
    {
        switch (action)
        {
        case GLFW_PRESS:
            Controls.SKeyState = true;
            break;

        case GLFW_REPEAT:
            break;

        case GLFW_RELEASE:
            Controls.SKeyState = false;
            break;
        }
    }
    break;

    case GLFW_KEY_A:
    {
        switch (action)
        {
        case GLFW_PRESS:
            Controls.AKeyState = true;
            break;

        case GLFW_REPEAT:
            break;

        case GLFW_RELEASE:
            Controls.AKeyState = false;
            break;
        }
    }
    break;

    case GLFW_KEY_D:
    {
        switch (action)
        {
        case GLFW_PRESS:
            Controls.DKeyState = true;
            break;

        case GLFW_REPEAT:
            break;

        case GLFW_RELEASE:
            Controls.DKeyState = false;
            break;
        }
    }
    break;

    case GLFW_KEY_E:
    {
        switch (action)
        {
        case GLFW_PRESS:
            Controls.EKeyState = true;
            break;

        case GLFW_REPEAT:
            break;

        case GLFW_RELEASE:
            Controls.EKeyState = false;
            break;
        }
    }
    break;

    case GLFW_KEY_Q:
    {
        switch (action)
        {
        case GLFW_PRESS:
            Controls.QKeyState = true;
            break;

        case GLFW_REPEAT:
            break;

        case GLFW_RELEASE:
            Controls.QKeyState = false;
            break;
        }
    }
    break;
    }
}


void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
   
}

void glfw_window_size_callback(GLFWwindow* window, int width, int height) 
{
    WindowWidth = width;
    WindowHeight = height;
}

