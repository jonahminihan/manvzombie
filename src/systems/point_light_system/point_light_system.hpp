#pragma once
#include "mvz_pipeline.hpp"
#include "mvz_device.hpp"
#include "mvz_camera.hpp"
#include "mvz_game_object.hpp"
#include "mvz_frame_info.hpp"

#include <memory>
#include <vector>

namespace mvz {
    class PointLightSystem {
    public:
        PointLightSystem(MvzDevice &device, VkRenderPass renderPass, VkDescriptorSetLayout globalSetLayout);

        ~PointLightSystem();

        PointLightSystem(const PointLightSystem &) = delete;

        PointLightSystem &operator=(const PointLightSystem &) = delete;

        void update(FrameInfo &frameInfo, GlobalUbo &ubo);

        void render(FrameInfo &frameInfo);

    private:
        void createPipelineLayout(VkDescriptorSetLayout globalSetLayout);

        void createPipeline(VkRenderPass renderPass);


        MvzDevice &mvzDevice;
        std::unique_ptr<MvzPipeline> mvzPipeline;
        VkPipelineLayout pipelineLayout;
    };
}
