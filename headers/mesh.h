#pragma once
#include "../common.h"

class Vertex
{
private:
    glm::vec3 pos;
public:
    Vertex(const glm::vec3& pos);
    ~Vertex();
};

Vertex::Vertex(const glm::vec3& pos)
{
    this->pos = pos;
}

Vertex::~Vertex()
{
}


class Mesh
{
private:
    enum{
        POSITION_VB,
        NUM_BUFFERS
    };

    GLuint vertArrObj;
    GLuint vertArrBuf[NUM_BUFFERS];
    unsigned int drawCount;
public:
    Mesh(Vertex* verticies, unsigned int numVerts);
    ~Mesh();

    void draw ();
};

Mesh::Mesh(Vertex* verticies, unsigned int numVerts)
{
    drawCount = numVerts;
    glGenVertexArrays(1,&vertArrObj);
    glBindVertexArray(vertArrObj);

    glGenBuffers(NUM_BUFFERS,vertArrBuf);
    glBindBuffer(GL_ARRAY_BUFFER,vertArrBuf[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(verticies[0]),verticies,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

    glBindVertexArray(0);

}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1,&vertArrObj);
}

void Mesh::draw()
{
    glBindVertexArray(vertArrObj);

    glDrawArrays(GL_TRIANGLES,0,drawCount);

    glBindVertexArray(0);
}
