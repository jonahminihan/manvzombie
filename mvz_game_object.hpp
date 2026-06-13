#pragma once

#include "mvz_model.hpp"

#include <memory>

namespace mvz {
    struct Transform2dComponent {
        glm::vec2 translation{}; // position offset
        glm::vec2 scale{1.f, 1.f};
        float rotation;

        glm::mat2 mat2() {
            const float s = glm::sin(rotation);
            const float c = glm::cos(rotation);
            glm::mat2 rotMatric{{c, s}, {-s, c}};
            
            glm::mat2 scaleMat{{scale.x, 0.0f}, {0.0f, scale.y}};
            return rotMatric * scaleMat;
        }
    };

    class MvzGameObject {
    public:
        using id_t = unsigned int;

        static MvzGameObject createGameObject() {
            static id_t currentId = 0;
            return MvzGameObject{currentId++};
        }

        MvzGameObject(const MvzGameObject &) = default;

        MvzGameObject &operator=(const MvzGameObject &) = default;

        MvzGameObject(MvzGameObject &&) = default;

        MvzGameObject &operator=(MvzGameObject &&) = default;

        [[nodiscard]] id_t getId() const {
            return id;
        }

        std::shared_ptr<MvzModel> model{};
        glm::vec3 color{};
        Transform2dComponent transform2d{};

    private:
        MvzGameObject(id_t objId) : id{objId} {
        };

        id_t id;
    };
}
