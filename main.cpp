#include "common.h"
#include "headers/display.h"

int main(int argc,char *argv[])
{
    Display test (800,600,"YATTA");

    while (!test.IsClosed())
    {
        glClearColor(0.0f,0.15f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        test.update();
    }
    return 0;
}

/*  // SDL init
    if (SDL_Init(SDL_INIT_NOPARACHUTE) && SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Unable to initialise SDL: %s", SDL_GetError());
        return -1;
    }
    else SDL_Log("SDL Initialised");
    SDL_Window* window = SDL_CreateWindow(
        "Test",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_OPENGL
    );

    // Gen an OpenGL context and map to window instance
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    bool isRunning = true;
    while (isRunning)
    {
        // Ready buffers, and switch
        SDL_GL_SwapWindow(window);

    }


    // Clean up
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);


    std::cout << "YATTA\n";
    return 0;
} */