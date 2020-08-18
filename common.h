#pragma once

// Standard
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

// OpenGL
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>

//#define ASSERT(x) if (!(x)) ;
/* #define GLCall(x) GLClearErr();\
    x;\
    GLLogCall() */

/*
void
GLClearErr()
{
    while (!glGetError());
}

bool
GLLogCall()
{
    while (GLenum error = glGetError()){
        std::cout << "[OpenGL Error]: " << error << std::endl;
        return false;
    }
    return true;
} */
