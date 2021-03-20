#ifndef CAMERA_H
#define CAMERA_H

#include <glm.hpp>
#include <gtc/constants.hpp>

class Camera
{
public:
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), float yaw = glm::pi<float>(), float pitch = 0.0f);

    glm::mat4 getViewMatrix() const;

    void setPosition(const glm::vec3& pos);
    void rotate(float yaw, float pitch);
    void move(const glm::vec3& offsetPos);

    const glm::vec3& getLook() const;
    const glm::vec3& getRight() const;
    const glm::vec3& getUp() const;

    float getFieldOfView() const;
    void setFieldOfView(float fieldOfView);

private:
    const glm::vec3 worldUp;

    glm::vec3 pos;
    glm::vec3 targetPos;
    glm::vec3 up;
    glm::vec3 look;
    glm::vec3 right;

    float yaw;
    float pitch;

    float fieldOfView;

    void updateCameraVectors();
};

#endif // CAMERA_H