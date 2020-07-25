#pragma once
#include "../common.h"

/* the file doesnt follow 
 *benny boxs tutorial directly 
 *there are some liberties taken 
 *and some errors are created 
 */

class Shader
{
private:
    static const unsigned short NUM_SHADERS = 2;
    
    GLuint prog;
    GLuint uintshaders[NUM_SHADERS];
public:
    Shader(const std::string& filename);
    ~Shader();
    void bind();
};

static void CheckShaderError(GLuint shader, GLint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& filename);
static GLuint createShader (const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& filename)
{
    prog = glCreateProgram();
    uintshaders[0] = createShader(LoadShader(filename + ".vs"),GL_VERTEX_SHADER);
    uintshaders[0] = createShader(LoadShader(filename + ".fs"),GL_FRAGMENT_SHADER);

    for(int i = 0; i < NUM_SHADERS; i++)
        glAttachShader(prog,uintshaders[i]);

    glBindAttribLocation(prog,0,"position");
    
    glLinkProgram(prog);
    CheckShaderError(prog, GL_LINK_STATUS, true, "ERROR: program linking faild");

    glValidateProgram(prog);
    CheckShaderError(prog, GL_VALIDATE_STATUS, true, "ERROR: program validation faild");
}

Shader::~Shader()
{
    glDeleteProgram(prog);
}

void Shader::bind()
{
    for(int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(prog,uintshaders[i]);
        glDeleteShader(uintshaders[i]);
    }
    glUseProgram(prog);
}

static GLuint createShader (const std::string& text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    if(shader == 0)
        std::cerr << "Error: shader creation failed\n";
    
    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];
    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    glShaderSource(shader,1,shaderSourceStrings,shaderSourceStringLengths);
    glCompileShader(shader);
    
    CheckShaderError(shader, GL_COMPILE_STATUS, false, "ERROR: shader compilation fail: ");
    return shader;
}

static void 
CheckShaderError(GLuint shader, GLint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if (isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        
        std::cerr << errorMessage << ": " << error << ". \n";
    }
}

static std::string 
LoadShader(const std::string& filename)
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
        std::cerr << "Unable to load shader: " << filename << std::endl;
    
    return output;
}
