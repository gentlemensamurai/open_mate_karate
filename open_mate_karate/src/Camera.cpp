#include "Camera.h"
#include <gtc/matrix_transform.hpp>

void Camera::rotate(float yaw, float pitch)
{

}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(pos, targetPos, up);
}

Camera::Camera()
    : pos(glm::vec3(0.0f, 0.0f, 0.0f)),
      targetPos(glm::vec3(0.0f, 0.0f, 0.0f)),
      up(glm::vec3(0.0f, 1.0f, 0.0f)),
      yaw(0.0f),
      pitch(0.0f)
{
    
}