#ifndef ORBIT_CAMERA_H
#define ORBIT_CAMERA_H

#include "Camera.h"

class OrbitCamera : public Camera
{
public:
    OrbitCamera();

    virtual void rotate(float yaw, float pitch);

    void setLookAt(const glm::vec3& target);
    void setRadius(float radius);

private:
    float radius;

    void updateCameraVectors();

};

#endif // ORBIT_CAMERA_H