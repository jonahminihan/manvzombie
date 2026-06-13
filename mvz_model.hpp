#pragma once
#include "mvz_device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

namespace mvz {
    class MvzModel {
    public:
        struct Vertex {
            glm::vec2 position;
            glm::vec3 color;

            static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();

            static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
        };

        MvzModel(MvzDevice &device, const std::vector<Vertex> &vertices);

        ~MvzModel();

        MvzModel(const MvzModel &) = delete;

        MvzModel &operator=(const MvzModel &) = delete;

        void bind(VkCommandBuffer command_buffer);

        void draw(VkCommandBuffer command_buffer);

    private:
        void createVertexBuffers(const std::vector<Vertex> &vertices);

        MvzDevice &mvzDevice;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;
    };
}
