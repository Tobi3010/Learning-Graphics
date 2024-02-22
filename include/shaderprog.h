#ifndef SHADERPROG_HPP
#define SHADERPROG_HPP

#include <string>
class ShaderProg
{
public:
    ShaderProg();

    ~ShaderProg();

    void attach(const char *fileName, unsigned int shaderType);

    void link();

    void use();

private:
    unsigned int m_pId;

    std::string readShaderFromFile(const char *fileName);
};

#endif