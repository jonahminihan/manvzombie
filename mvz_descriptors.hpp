#pragma once

#include "mvz_device.hpp"

// std
#include <memory>
#include <unordered_map>
#include <vector>

namespace mvz {
    class MvzDescriptorSetLayout {
    public:
        class Builder {
        public:
            Builder(MvzDevice &mvzDevice) : mvzDevice{mvzDevice} {
            }

            Builder &addBinding(
                uint32_t binding,
                VkDescriptorType descriptorType,
                VkShaderStageFlags stageFlags,
                uint32_t count = 1);

            std::unique_ptr<MvzDescriptorSetLayout> build() const;

        private:
            MvzDevice &mvzDevice;
            std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings{};
        };

        MvzDescriptorSetLayout(
            MvzDevice &mvzDevice, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings);

        ~MvzDescriptorSetLayout();

        MvzDescriptorSetLayout(const MvzDescriptorSetLayout &) = delete;

        MvzDescriptorSetLayout &operator=(const MvzDescriptorSetLayout &) = delete;

        VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; }

    private:
        MvzDevice &mvzDevice;
        VkDescriptorSetLayout descriptorSetLayout;
        std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings;

        friend class MvzDescriptorWriter;
    };

    class MvzDescriptorPool {
    public:
        class Builder {
        public:
            Builder(MvzDevice &mvzDevice) : mvzDevice{mvzDevice} {
            }

            Builder &addPoolSize(VkDescriptorType descriptorType, uint32_t count);

            Builder &setPoolFlags(VkDescriptorPoolCreateFlags flags);

            Builder &setMaxSets(uint32_t count);

            std::unique_ptr<MvzDescriptorPool> build() const;

        private:
            MvzDevice &mvzDevice;
            std::vector<VkDescriptorPoolSize> poolSizes{};
            uint32_t maxSets = 1000;
            VkDescriptorPoolCreateFlags poolFlags = 0;
        };

        MvzDescriptorPool(
            MvzDevice &mvzDevice,
            uint32_t maxSets,
            VkDescriptorPoolCreateFlags poolFlags,
            const std::vector<VkDescriptorPoolSize> &poolSizes);

        ~MvzDescriptorPool();

        MvzDescriptorPool(const MvzDescriptorPool &) = delete;

        MvzDescriptorPool &operator=(const MvzDescriptorPool &) = delete;

        bool allocateDescriptor(
            const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet &descriptor) const;

        void freeDescriptors(std::vector<VkDescriptorSet> &descriptors) const;

        void resetPool();

    private:
        MvzDevice &mvzDevice;
        VkDescriptorPool descriptorPool;

        friend class MvzDescriptorWriter;
    };

    class MvzDescriptorWriter {
    public:
        MvzDescriptorWriter(MvzDescriptorSetLayout &setLayout, MvzDescriptorPool &pool);

        MvzDescriptorWriter &writeBuffer(uint32_t binding, VkDescriptorBufferInfo *bufferInfo);

        MvzDescriptorWriter &writeImage(uint32_t binding, VkDescriptorImageInfo *imageInfo);

        bool build(VkDescriptorSet &set);

        void overwrite(VkDescriptorSet &set);

    private:
        MvzDescriptorSetLayout &setLayout;
        MvzDescriptorPool &pool;
        std::vector<VkWriteDescriptorSet> writes;
    };
}
