#include "common.h"
#include "headers/display.h"
#include "headers/shader.h"
#include "headers/mesh.h"

int main(int argc,char *argv[])
{
    Display test (800,600,"YATTA");

    Vertex verticies[] = {
        Vertex(glm::vec3(0,0.5,0)),
        Vertex(glm::vec3(-0.5,-0.5,0)),
        Vertex(glm::vec3(0.5,-0.5,0))
    };

    Mesh mesh(verticies,sizeof(verticies)/sizeof(verticies[0]));

    Shader shader("./res/basicShader");
    
    while (!test.IsClosed())
    {
        test.clear(0.25,0.25,0.25,1.0);

        shader.bind();
        mesh.draw();

        test.update();
    }
    return 0;
}