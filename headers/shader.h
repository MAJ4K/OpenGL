#pragma once
#include "GL/glew.h"
#include <fstream>
#include <math.h>
#include <unordered_map>
#include "glm/glm.hpp"

class Shader
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    //caching for uniforms
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader(std::string);
    ~Shader();

    void bind() const;
    void unbind() const;

    //uniforms
    void setUniform4f(const std::string& name, float v0,float v1,float v2,float v3);
    void setUniform1i(const std::string& name, int value);
    void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
    int getUniform(std::string name);
};

////////////////////////////////////////////
//////////////////////////////////////////////////
/////////////////////////////////////////////////////////

static std::string 
ftos(const std::string& filename)
{
    std::ifstream file;
    file.open(filename.c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while (file.good())
        {
            getline(file,line);
            output.append(line + "\n");
        }
    }
    else 
        std::cerr << "Unable to load file: " << filename << std::endl;
    
    return output;
}

static unsigned int
compileShader (unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length; 
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "[Failed to Compile Shader]" << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int
createshader(const std::string& vertexShader, const std::string& fragShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER,fragShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

//////////////////
////////////////////////
///////////////////////////////

Shader::Shader(std::string filePath):
    m_FilePath(filePath)
{
    std::string fs = ftos(filePath + ".fs");
    std::string vs = ftos(filePath + ".vs");

    m_RendererID = createshader(vs,fs);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

void Shader::setUniform1i(const std::string& name, int value)
{
    glUniform1i(getUniform(name),value);
}

void Shader::setUniform4f(const std::string& name, float v0,float v1,float v2,float v3)
{
    glUniform4f(getUniform(name),v0,v1,v2,v3);
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(getUniform(name),1,GL_FALSE,&matrix[0][0]);
}

//PRIVATE
int Shader::getUniform(std::string name)
{
    int location;
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        location = m_UniformLocationCache[name];
    else
        m_UniformLocationCache[name] = 
        location = 
        glGetUniformLocation(m_RendererID,name.c_str());

    if (location < 0)
        std::cout << "Warning uniform " << name << " doesnt exist!\n";
    return location;
}