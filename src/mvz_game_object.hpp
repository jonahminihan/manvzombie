#pragma once

#include "mvz_model.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <memory>
#include <unordered_map>

namespace mvz {
    struct TransformComponent {
        glm::vec3 translation{}; // position offset
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec3 rotation;

        // Matrix corrsponds to Translate * Ry * Rx * Rz * Scale
        // Rotations correspond to Tait-bryan angles of Y(1), X(2), Z(3)
        // https://en.wikipedia.org/wiki/Euler_angles#Rotation_matrix
        glm::mat4 mat4();

        glm::mat3 normalMatrix();
    };

    struct PointLightComponent {
        float lightIntensity = 1.0f;
    };

    class MvzGameObject {
    public:
        using id_t = unsigned int;
        using Map = std::unordered_map<id_t, MvzGameObject>;

        static MvzGameObject createGameObject() {
            static id_t currentId = 0;
            return MvzGameObject{currentId++};
        }

        static MvzGameObject makePointLight(float intensity = 10.0f, float radius = .1f,
                                            glm::vec3 color = glm::vec3(1.f));

        MvzGameObject(const MvzGameObject &) = default;

        MvzGameObject &operator=(const MvzGameObject &) = default;

        MvzGameObject(MvzGameObject &&) = default;

        MvzGameObject &operator=(MvzGameObject &&) = default;

        [[nodiscard]] id_t getId() const {
            return id;
        }

        glm::vec3 color{};
        TransformComponent transform{};

        // Optional pointer components
        std::shared_ptr<MvzModel> model{};
        std::unique_ptr<PointLightComponent> pointLight = nullptr;

    private:
        MvzGameObject(id_t objId) : id{objId} {
        };

        id_t id;
    };
}
