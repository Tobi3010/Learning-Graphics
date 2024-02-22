#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaderprog.h"

using namespace std;

// object id variables
unsigned int vertexBuffer;
unsigned int vertexArray;

// vertex of points

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};  

int main(int argc, char **argv)
{
    // initialize GLFW
    if (!glfwInit())
    {
        return -1;
    }

    // create a window pointer
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
    // error check
    if (window == NULL)
    {
        cout << "Error. I could not create a window at all!" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    ShaderProg myProgram;
    // attachment of shaders to program object
    myProgram.attach("../shaders/vs.glsl", GL_VERTEX_SHADER);
    myProgram.attach("../shaders/fs.glsl", GL_FRAGMENT_SHADER);
    myProgram.link();

    // buffer
    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myProgram.use();

        glBindVertexArray(vertexArray);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}