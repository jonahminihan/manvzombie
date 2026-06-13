#pragma once
#ifndef MANVZOMBIE_MVZ_PIPELINE_HPP
#define MANVZOMBIE_MVZ_PIPELINE_HPP
#include <string>
#include <vector>
#include "mvz_device.hpp"
#endif //MANVZOMBIE_MVZ_PIPELINE_HPP

namespace mvz {
    struct PipelineConfigInfo {
        PipelineConfigInfo() = default;

        PipelineConfigInfo(const PipelineConfigInfo &) = delete;

        PipelineConfigInfo &operator=(const PipelineConfigInfo &) = delete;

        VkPipelineViewportStateCreateInfo viewportInfo;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        std::vector<VkDynamicState> dynamicStateEnables;
        VkPipelineDynamicStateCreateInfo dynamicStateInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class MvzPipeline {
    public:
        MvzPipeline(MvzDevice &device, const std::string &vertFilePath, const std::string &fragFilePath,
                    const PipelineConfigInfo &configInfo);

        ~MvzPipeline();

        MvzPipeline(const MvzPipeline &) = delete;

        MvzPipeline &operator=(const MvzPipeline &) = delete;

        void bind(VkCommandBuffer commandBuffer);

        static void defaultPipelineConfigInfo(PipelineConfigInfo &configInfo);

    private:
        static std::vector<char> readFile(const std::string &filePath);

        void createGraphicsPipeline(const std::string &vertFilePath, const std::string &fragFilePath,
                                    const PipelineConfigInfo &configInfo);

        void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);

        MvzDevice &mvzDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };
}
