#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaderprog.h"
#include <cmath>

using namespace std;

// object id variable
unsigned int VAO_1;
unsigned int VBO_1;
unsigned int VAO_2;
unsigned int VBO_2;
unsigned int VAOs[2] = {VAO_1, VAO_2};
unsigned int VBOs[2] = {VBO_1, VBO_2};

unsigned int EBO;

// vertex of points
float vertices[] = {
     1.0f,  0.0f, 0.0f,  // top right
     1.0f, 0.5f, 0.0f,  // bottom right
     0.0f, 0.0f, 0.0f,  // bottom left
    -1.0f,  0.0f, 0.0f,   // top left 
    -1.0f, -0.5f, 0.0f,
     0.0f, 0.0f, 0.0f
};

/*
unsigned int indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  
*/

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

    ShaderProg orangeProgram;
    // attachment of shaders to program object
    orangeProgram.attach("../shaders/vs.glsl", GL_VERTEX_SHADER);
    orangeProgram.attach("../shaders/fs-orange.glsl", GL_FRAGMENT_SHADER);
    orangeProgram.link();

    ShaderProg yellowProgram;
    yellowProgram.attach("../shaders/vs.glsl", GL_VERTEX_SHADER);
    yellowProgram.attach("../shaders/fs-yellow.glsl", GL_FRAGMENT_SHADER);
    yellowProgram.link();

    ShaderProg uniformProgram;
    uniformProgram.attach("../shaders/vs.glsl", GL_VERTEX_SHADER);
    uniformProgram.attach("../shaders/uniform.glsl", GL_FRAGMENT_SHADER);
    uniformProgram.link();



    ShaderProg programs[2] = {orangeProgram, yellowProgram};

    for (int i = 0; i <= sizeof(VAOs)/sizeof(VAOs[0]); i += 1) {
        glGenVertexArrays(1, &VAOs[i]);
        glGenBuffers(1, &VBOs[i]);

        glBindVertexArray(VAOs[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)/2, vertices + (i * 9), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        
    }
   
    /*
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    */

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i <= sizeof(VAOs)/sizeof(VAOs[0]); i += 1) {
            uniformProgram.use();

            glBindVertexArray(VAOs[i]);

            double  timeValue = glfwGetTime();
            float greenValue = static_cast<float>(sin(timeValue) / 2.0 + 0.5);
            int vertexColorLocation = glGetUniformLocation(uniformProgram.id(), "ourColor");
            glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
           
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}