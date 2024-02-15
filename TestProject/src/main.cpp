#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

// vertex shader source code
char *vsSrc =
    "#version 330 core\n                                    \
 layout (location = 0) in vec3 inPosition;              \
 void main()                                            \    
 {                                                      \
    gl_Position = vec4(inPosition, 1.0);                \
 }";
// fragment shader source code
char *fsSrc =
    "#version 330 core\n                                    \
 out vec4 fragColor;                                    \
 void main()                                            \    
 {                                                      \
    fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);           \
 }";

// object id variables
unsigned int pId;
unsigned int vertexShaderId;
unsigned int fragmentShaderId;
unsigned int vertexBuffer;
unsigned int vertexArray;

// vertex of points

float vertices[] = {
    -0.8f, -0.6f, 0.0f,
    0.3f, -0.4f, 0.0f,
    0.0f, 0.2f, 0.0f};

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

    // create program object
    pId = glCreateProgram();

    // create shaders
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId, 1, &vsSrc, NULL);
    glCompileShader(vertexShaderId);

    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fsSrc, NULL);
    glCompileShader(fragmentShaderId);

    // attachment of shaders to program object
    glAttachShader(pId, vertexShaderId);
    glAttachShader(pId, fragmentShaderId);

    glLinkProgram(pId);

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

        glUseProgram(pId);

        glBindVertexArray(vertexArray);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}