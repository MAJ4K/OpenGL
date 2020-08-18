#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "primatives.h"

class Mesh
{
private:
    enum Attributes
    {
        ATTRIB_POSITION,
        ATTRIB_TEXCOORD,
        ATTRIB_NORMAL,

        NUM_ATTRIBS
    };
    enum Buffers
    {
        BUFF_VERTEX,
        BUFF_INDEX,

        NUM_BUFFERS
    };
    unsigned int m_vertexArray;
    unsigned int m_buffers[NUM_BUFFERS];
    unsigned int m_drawCount;
public:
    Mesh(const Vertex* verticies, unsigned int numVerts,const unsigned int* indices, unsigned int numInds);
    ~Mesh();
    void draw();
};

Mesh::Mesh(const Vertex* verticies, unsigned int numVerts,const unsigned int* indices, unsigned int numInds):
    m_drawCount(numInds)
{
    //Vertex Array
    glGenVertexArrays(1,&m_vertexArray);
    glBindVertexArray(m_vertexArray);

    //Buffers
    glGenBuffers(NUM_BUFFERS,m_buffers);
        //Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER,m_buffers[BUFF_VERTEX]);
    glBufferData(GL_ARRAY_BUFFER,numVerts * sizeof(verticies[0]),verticies,GL_STATIC_DRAW);
        //Index Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_buffers[BUFF_INDEX]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,numInds * sizeof(int),indices,GL_STATIC_DRAW);

    unsigned char attrib = ATTRIB_POSITION;
    Attrib_Detail aH[] ={
        Attrib_Detail {GL_FLOAT,GL_FALSE,3,0},
        Attrib_Detail {GL_FLOAT,GL_FALSE,2,sizeof(float)*3},
        Attrib_Detail {GL_FLOAT,GL_FALSE,3,sizeof(float)*5}
    };
    for (; attrib < NUM_ATTRIBS; attrib++)
    {
        glEnableVertexAttribArray(attrib);
        glVertexAttribPointer(attrib,
        aH[attrib].prim,
        aH[attrib].type,
        aH[attrib].norm,
        sizeof(Vertex),
        (const void*)aH[attrib].offset);
    }
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1,&m_vertexArray);
}

void Mesh::draw()
{
    glBindVertexArray(m_vertexArray);

    glDrawElements(GL_TRIANGLES,m_drawCount,GL_UNSIGNED_INT,nullptr);

    glBindVertexArray(0);
}
