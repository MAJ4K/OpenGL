#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>
#include <GL/glew.h>

class Texture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_width, m_height, m_BPP;
public:
    Texture(const std::string& filePath);
    ~Texture();

    void bind(unsigned int slot) const;
    void unbind() const;

    inline int getWidth() const {return m_width;}
    inline int getHeight() const {return m_height;}
    inline int getBPP() const {return m_BPP;}

};

Texture::Texture(const std::string& filePath):
    m_RendererID(0),
    m_FilePath(filePath),m_LocalBuffer(nullptr),
    m_width(0),m_height(0),m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(filePath.c_str(),&m_width,&m_height,&m_BPP,4);

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D,m_RendererID);

    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA8,m_width,m_height,0,GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if(m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_RendererID);
}

void Texture::bind(unsigned int slot = 0) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D,m_RendererID);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}