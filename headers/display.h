#pragma once
#include "../common.h"

class Display
{
private:
    SDL_Window* winptr;
    SDL_GLContext glcontx;
    bool isClosed;
public:
    Display(unsigned short width, unsigned short height, const char* title);
    ~Display();

    void clear(float r, float g, float b, float a);
    void update();
    bool IsClosed(){return isClosed;}
};

Display::Display(unsigned short width,unsigned short height,const char* title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    winptr = SDL_CreateWindow(title, 
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    width,
    height,
    SDL_WINDOW_OPENGL);

    glcontx = SDL_GL_CreateContext(winptr);

    GLenum status = glewInit();

    if (status != GLEW_OK)
    {
        std::cerr << "Glew failed initialization\n";
    }

    isClosed = false;
}

Display::~Display()
{
    SDL_GL_DeleteContext(glcontx);
    SDL_DestroyWindow(winptr);
    SDL_Quit();
}

void Display::clear(float r, float g, float b, float a)
{
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Display::update()
{
    SDL_GL_SwapWindow(winptr);

    SDL_Event e;
    
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
            isClosed = true;
    }
}