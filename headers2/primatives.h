#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 pos;
    glm::vec2 txcoord;
    glm::vec3 normals;
};
struct Attrib_Detail
{
    unsigned int type;
    unsigned int norm;
    unsigned char prim;
    unsigned char offset;
};

//Square
namespace Square
{
    static const Vertex verticies[8] =
    {
        Vertex {glm::vec3(-0.5f,-0.5f,-0.5f), glm::vec2(0.0f,0.0f), glm::vec3(-0.57735021f,-0.57735021f,-0.57735021f)}, // 0
        Vertex {glm::vec3(-0.5f, 0.5f,-0.5f), glm::vec2(0.0f,1.0f), glm::vec3(-0.57735021f, 0.57735021f,-0.57735021f)}, // 1
        Vertex {glm::vec3( 0.5f,-0.5f,-0.5f), glm::vec2(1.0f,0.0f), glm::vec3( 0.57735021f,-0.57735021f,-0.57735021f)}, // 2
        Vertex {glm::vec3( 0.5f, 0.5f,-0.5f), glm::vec2(1.0f,1.0f), glm::vec3( 0.57735021f, 0.57735021f,-0.57735021f)}, // 3
        Vertex {glm::vec3(-0.5f,-0.5f, 0.5f), glm::vec2(1.0f,0.0f), glm::vec3(-0.57735021f,-0.57735021f, 0.57735021f)}, // 4
        Vertex {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f,1.0f), glm::vec3(-0.57735021f, 0.57735021f, 0.57735021f)}, // 5
        Vertex {glm::vec3( 0.5f,-0.5f, 0.5f), glm::vec2(0.0f,0.0f), glm::vec3( 0.57735021f,-0.57735021f, 0.57735021f)}, // 6
        Vertex {glm::vec3( 0.5f, 0.5f, 0.5f), glm::vec2(0.0f,1.0f), glm::vec3( 0.57735021f, 0.57735021f, 0.57735021f)}, // 7
    };
    static const unsigned int indices[36] =
    {
        0,1,2,//front
        1,2,3,
        4,5,6,//back
        5,6,7,
        0,1,4,//left
        1,4,5,
        2,3,6,//right
        3,6,7,
        1,3,5,//top
        3,5,7,
        0,2,4,//bottom
        2,4,6 
    };
};

// Plane/Quad
namespace Quad
{
    static const Vertex verticies[4] =
    {
        Vertex {glm::vec3(-0.5f,-0.5f,0), glm::vec2(0.0f,0.0f), glm::vec3(0,0,-1)}, // 0
        Vertex {glm::vec3(-0.5f, 0.5f,0), glm::vec2(0.0f,1.0f), glm::vec3(0,0,-1)}, // 1
        Vertex {glm::vec3( 0.5f,-0.5f,0), glm::vec2(1.0f,0.0f), glm::vec3(0,0,-1)}, // 2
        Vertex {glm::vec3( 0.5f, 0.5f,0), glm::vec2(1.0f,1.0f), glm::vec3(0,0,-1)}, // 3
    };
    static const unsigned int indices[6] =
    {
        0,1,2,
        1,2,3
    };
};
