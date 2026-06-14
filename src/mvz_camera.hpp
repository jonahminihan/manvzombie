#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

namespace mvz {
    class MvzCamera {
    public:
        // points identified: (left, bottom, near) (right, top, far)
        void setOrthographicProjection(float left, float right, float top, float bottom, float near, float far);

        // fovy = Field of view Y, Aspect ratio (width/height), near and far clipping planes
        void setPerspectiveProjection(float fovy, float aspect, float near, float far);

        // position of the camera, direction the camera is pointing, and what vector is facing up
        void setViewDirection(glm::vec3 position, glm::vec3 direction, glm::vec3 up = glm::vec3(0.0f, -1.0f, 0.0f));

        void setViewTarget(glm::vec3 position, glm::vec3 target, glm::vec3 up = glm::vec3(0.0f, -1.0f, 0.0f));

        // Use Euler angles to specify the orientation of the camera
        void setViewYXZ(glm::vec3 position, glm::vec3 rotation);

        const glm::mat4 &getProjection() const { return projectionMatrix; }
        const glm::mat4 &getView() const { return viewMatrix; }

    private:
        glm::mat4 projectionMatrix{1.f};
        glm::mat4 viewMatrix{1.f};
    };
}
