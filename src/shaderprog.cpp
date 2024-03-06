#include "shaderprog.h"
#include <glad/glad.h>
#include <fstream>
#include <iostream>

ShaderProg::ShaderProg()
{
    // constructor

    m_pId = glCreateProgram();
}
ShaderProg::~ShaderProg(){
    //destructor
    glDeleteProgram(m_pId);
}


int ShaderProg::id(){
    return(m_pId);
}


void ShaderProg::link()
{
    // links the shader object into the program object
    glLinkProgram(m_pId);
    // check if it is linked
    int isLinked;
    char logMsg[512];
    glGetShaderiv(m_pId, GL_LINK_STATUS, &isLinked);
    if (!isLinked)
    {
        glGetProgramInfoLog(m_pId, 512, 0, logMsg);
        std::cout << "Program Linking error: " << std::endl
                  << logMsg << std::endl;
    }
}

void ShaderProg::use()
{
    glUseProgram(m_pId);
}



void ShaderProg::attach(const char *fileName, unsigned int shaderType)
{
    // create a shader object
    unsigned int shaderId = glCreateShader(shaderType);
    // get shader code
    std::string srcCode = readShaderFromFile(fileName);
    // define shader code
    const char *chSrcCode = &srcCode[0];
    glShaderSource(shaderId, 1, &chSrcCode, 0);
    // compile the shader object
    glCompileShader(shaderId);

    int isCompiled;
    char logMsg[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled)
    {
        glGetShaderInfoLog(shaderId, 512, 0, logMsg);
        std::cout << "ShaderType: " << shaderType << std::endl
                << logMsg << std::endl;
    }


    // attach shader object to the program object
    glAttachShader(m_pId, shaderId);
    // after adding the shader object, we don't need it anymore
    glDeleteShader(shaderId);

}

std::string ShaderProg::readShaderFromFile(const char *fileName)
{
    // reads the source code from the shader source file

    std::ifstream file(fileName);
    std::string stringData;
    if (file.is_open())
    {
        char aChar;
        // read each character one by one
        while ((aChar = file.get()) != EOF)
        {
            stringData += aChar;
        }
        file.close();
    }
    return stringData;
}