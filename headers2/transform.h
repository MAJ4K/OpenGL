#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform
{
private:
    glm::vec3 m_position;
    glm::vec3 m_rotation;
    glm::vec3 m_scale;
public:
    Transform(glm::vec3 pos = glm::vec3(),
    glm::vec3 rot = glm::vec3(),
    glm::vec3 scl = glm::vec3(1.0f)):
        m_position(pos),m_rotation(rot),m_scale(scl)
    {

    }
    ~Transform(){}

    inline glm::mat4 getModel() const
    {
        glm::mat4 posMatrix = glm::translate(m_position);
        glm::mat4 rotxMat = glm::rotate(m_rotation.x,glm::vec3(1,0,0));
        glm::mat4 rotyMat = glm::rotate(m_rotation.y,glm::vec3(0,1,0));
        glm::mat4 rotzMat = glm::rotate(m_rotation.z,glm::vec3(0,0,1));
        glm::mat4 scaleMatrix = glm::scale(m_scale);

        return posMatrix * rotzMat * rotyMat * rotxMat * scaleMatrix;
    }

    inline glm::vec3& getPos() {return m_position;}
    inline glm::vec3& getRot() {return m_rotation;}
    inline glm::vec3& getScl() {return m_scale;}
};