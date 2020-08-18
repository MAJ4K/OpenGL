#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace DCam
{
    struct Camera
    {
        char mode = -1;
        double aspect, fov;
        double near, far;
        glm::mat4 projectionMatrix;
        glm::vec3 position;
        //Perspective
        glm::vec3 forward;// unionizing needed
        glm::vec3 up;
        //Orthographic
        glm::vec3 rotation;// unionizing needed
    };

    void DCam_init(Camera& camera)
    {
        camera.position = (glm::vec3(0));
        //Perspective
        switch (camera.mode)
        {
        case 1:
        camera.projectionMatrix =
        glm::perspective(camera.fov,camera.aspect,camera.near,camera.far);
        camera.forward = (glm::vec3(0,0,1));
        camera.up = (glm::vec3(0,1,0));
        return;
        //Orthographic
        case 0:
        camera.fov = 1.0;
        camera.projectionMatrix =
        glm::ortho(-camera.aspect,camera.aspect,-camera.fov,camera.fov,
        camera.near,camera.far);
        return;
        }
    }

    glm::mat4 GetViewProjection(const Camera& camera)
    {
        switch (camera.mode)
        {
        case 1:
            return camera.projectionMatrix 
            * glm::lookAt(camera.position,camera.position+camera.forward,camera.up);
        case 0:
            glm::mat4 transform = glm::translate(glm::mat4(1.0f),camera.position)
            * glm::rotate(glm::mat4(1.0f),camera.forward.z,glm::vec3(0,0,1))
            * glm::rotate(glm::mat4(1.0f),camera.forward.y,glm::vec3(0,1,0))
            * glm::rotate(glm::mat4(1.0f),camera.forward.x,glm::vec3(1,0,0));
            return camera.projectionMatrix * glm::inverse(transform);
        }
        return glm::mat4(1);
    }
} // namespace Camera
