#include "Camera.h"
#include <gtc/matrix_transform.hpp>

const float defaultFieldOfView { 45.0f };

Camera::Camera(glm::vec3 pos, float yaw, float pitch)
    : worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
      pos(pos),
      targetPos(glm::vec3(0.0f, 0.0f, 0.0f)),
      up(glm::vec3(0.0f, 1.0f, 0.0f)),
      look(glm::vec3(0.0f, 0.0f, 0.0f)),
      right(glm::vec3(0.0f, 0.0f, 0.0f)),
      yaw(yaw),
      pitch(pitch),
      fieldOfView(defaultFieldOfView)
{
    updateCameraVectors();
}

void Camera::setPosition(const glm::vec3& pos)
{
    this->pos = pos;
}

void Camera::rotate(float yaw, float pitch)
{
    this->yaw += glm::radians(yaw);
    this->pitch += glm::radians(pitch);

    this->pitch = glm::clamp(this->pitch, -glm::pi<float>() / 2.0f + 0.1f, glm::pi<float>() / 2.0f - 0.1f);
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(this->pos, this->targetPos, this->up);
}

void Camera::move(const glm::vec3& offsetPos)
{
    this->pos += offsetPos;
    updateCameraVectors();
}

const glm::vec3& Camera::getLook() const
{
    return this->look;
}

const glm::vec3& Camera::getRight() const
{
    return this->right;
}

const glm::vec3& Camera::getUp() const
{
    return this->up;
}

const glm::vec3& Camera::getPos() const
{
    return this->pos;
}

float Camera::getFieldOfView() const
{
    return this->fieldOfView;
}

void Camera::setFieldOfView(float fieldOfView)
{
    this->fieldOfView = fieldOfView;
}

void Camera::updateCameraVectors()
{
    glm::vec3 newLook;
    newLook.x = cosf(this->pitch) * sinf(this->yaw);
    newLook.y = sinf(this->pitch);
    newLook.z = cosf(this->pitch) * cosf(this->yaw);

    this->look = glm::normalize(newLook);

    this->right = glm::normalize(glm::cross(this->look, worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->look));

    this->targetPos = this->pos + this->look;
}