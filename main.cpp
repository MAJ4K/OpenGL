#include <iostream>
// OpenGL
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include "headers/display.h"
#include "headers2/mesh.h"
#include "headers/shader.h"
#include "headers/texture.h"
#include "headers2/camera.h"
#include "headers2/transform.h"
#include "glm/gtc/matrix_transform.hpp"

int main (int argc, char* argv[])
{
    unsigned short dWidth = 1000;
    unsigned short dHeight = 600;
    float aspect = float(dWidth)/float(dHeight);
    Display display (dWidth,dHeight,"YATTA!");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    // Mesh
    Mesh mesh(Square::verticies,8,Square::indices,6 * 6);
    Mesh back(Quad::verticies,4,Quad::indices,6);
    Mesh bott(Quad::verticies,4,Quad::indices,6);

    //Camera
    DCam::Camera camera {1,aspect,70.0,0.01,1000.0};
    DCam::DCam_init(camera);

    //Transform
    Transform transl;

    //Shaders
    Shader def("./res/Shaders/defaultShader");
    Shader shader("./res/Shaders/basicShader");

    //Texture
    Texture texture("res/Textures/insta.png");
    texture.bind();
    shader.setUniform1i("u_texture",0);

    float r = 0.0f,p = 0.0f;
    while (!display.isClosed)
    {
        display.clear(0.1,0.1,0.1,1.0);
        r += 0.01;
        p += 0.033;
        float sir = sinf(r);
        float cor = cosf(r);

        def.bind();
        transl.getPos() = glm::vec3(0,0,3);
        transl.getRot() = glm::vec3(0);
        transl.getScl() = glm::vec3(5);
        def.setUniformMat4f("u_MVP",DCam::GetViewProjection(camera) * transl.getModel());
        def.setUniform4f("u_color", 0.1, 0.5f, 0.8f,1.0f);
        back.draw();

        transl.getPos() = glm::vec3(0,-2,0);
        transl.getRot() = glm::vec3(-30,0,0);
        transl.getScl() = glm::vec3(5);
        def.setUniformMat4f("u_MVP",DCam::GetViewProjection(camera) * transl.getModel());
        def.setUniform4f("u_color", 0.1, 0.5f, 0.8f,1.0f);
        back.draw();

        shader.bind();
        transl.getPos() = glm::vec3(0);
        transl.getScl() = glm::vec3(1);
        transl.getRot() = glm::vec3(sinf(p),p,r);
        camera.position = (glm::vec3( 5*cor,0,-5*abs(sir) ));
        camera.forward = (glm::vec3( -cor,0,abs(sir) ));
        shader.setUniformMat4f("u_MVP",DCam::GetViewProjection(camera) * transl.getModel());
        mesh.draw();

        display.update();
    }
}