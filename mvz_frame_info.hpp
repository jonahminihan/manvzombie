#pragma once

#include "mvz_camera.hpp"

#include <vulkan/vulkan.h>

namespace mvz {
    struct FrameInfo {
        int frameIndex;
        float frameTime;
        VkCommandBuffer commandBuffer;
        MvzCamera &camera;
    };
}
