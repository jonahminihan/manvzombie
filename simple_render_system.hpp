#pragma once
#include "mvz_pipeline.hpp"
#include "mvz_device.hpp"
#include "mvz_camera.hpp"
#include "mvz_game_object.hpp"
#include "mvz_frame_info.hpp"

#include <memory>
#include <vector>

namespace mvz {
    class SimpleRenderSystem {
    public:
        SimpleRenderSystem(MvzDevice &device, VkRenderPass renderPass);

        ~SimpleRenderSystem();

        SimpleRenderSystem(const SimpleRenderSystem &) = delete;

        SimpleRenderSystem &operator=(const SimpleRenderSystem &) = delete;

        void renderGameObjects(FrameInfo &frameInfo, std::vector<MvzGameObject> &gameObjects);

    private:
        void createPipelineLayout();

        void createPipeline(VkRenderPass renderPass);


        MvzDevice &mvzDevice;
        std::unique_ptr<MvzPipeline> mvzPipeline;
        VkPipelineLayout pipelineLayout;
    };
}
