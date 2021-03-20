#include "OrbitCamera.h"
#include <gtc/constants.hpp>

OrbitCamera::OrbitCamera()
    : radius(10.0f)
{

}

void OrbitCamera::rotate(float yaw, float pitch)
{
    this->yaw = glm::radians(yaw);
    this->pitch = glm::radians(pitch);

    this->pitch = glm::clamp(this->pitch, -glm::pi<float>() / 2.0f + 0.1f, glm::pi<float>() / 2.0f - 0.1f);

    updateCameraVectors();
}

void OrbitCamera::setLookAt(const glm::vec3& target)
{
    targetPos = target;
}

void OrbitCamera::setRadius(float radius)
{
    this->radius = glm::clamp(radius, 2.0f, 80.0f);
}

void OrbitCamera::updateCameraVectors()
{
    pos.x = targetPos.x + radius * cosf(pitch) * sinf(yaw);
    pos.y = targetPos.y + radius * sinf(pitch);
    pos.z = targetPos.z + radius * cosf(pitch) * cosf(yaw);
}