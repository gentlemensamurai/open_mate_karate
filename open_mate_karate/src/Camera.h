#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>

class Camera
{

public:
    virtual void rotate(float yaw, float pitch);

    glm::mat4 getViewMatrix() const;

protected:

    glm::vec3 pos;
    glm::vec3 targetPos;
    glm::vec3 up;

    float yaw;
    float pitch;

    Camera();

private:


};

#endif // CAMERA_H