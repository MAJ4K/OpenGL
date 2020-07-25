#include "common.h"
#include "headers/display.h"
#include "headers/shader.h"

int main(int argc,char *argv[])
{
    Display test (800,600,"YATTA");

    Shader shader("./res/basicShader");
    
    while (!test.IsClosed())
    {
        test.clear(0.25,0.25,0.25,1.0);

        test.update();
    }
    return 0;
}