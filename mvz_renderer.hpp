#pragma once
#include "mvz_window.hpp"
#include "mvz_device.hpp"
#include "mvz_swap_chain.hpp"

#include <cassert>
#include <memory>
#include <vector>

namespace mvz {
    class MvzRenderer {
    public:
        MvzRenderer(MvzWindow &mvzWindow, MvzDevice &mvzDevice);

        ~MvzRenderer();

        MvzRenderer(const MvzRenderer &) = delete;

        MvzRenderer &operator=(const MvzRenderer &) = delete;

        VkRenderPass getSwapChainRenderPass() const { return mvzSwapChain->getRenderPass(); };
        bool isFrameInProgress() const { return isFrameStarted; };

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
            return commandBuffers[currentFrameIndex];
        };

        int getFrameIndex() const {
            assert(isFrameStarted && "Cannot get frame index when frame not in progress");
            return currentFrameIndex;
        };

        VkCommandBuffer beginFrame();

        void endFrame();

        void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);

        void endSwapChainRenderPass(VkCommandBuffer commandBuffer);

    private:
        void createCommandBuffers();

        void freeCommandBuffers();

        void recreateSwapChain();

        MvzWindow &mvzWindow;
        MvzDevice &mvzDevice;
        std::unique_ptr<MvzSwapChain> mvzSwapChain;
        std::vector<VkCommandBuffer> commandBuffers;
        uint32_t currentImageIndex;
        int currentFrameIndex{0};
        bool isFrameStarted{false};
    };
}
