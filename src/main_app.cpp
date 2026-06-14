#include "main_app.hpp"
#include <stdexcept>

#include "mvz_buffer.hpp"
#include "simple_render_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "mvz_camera.hpp"
#include <chrono>
#include "keyboard_movement_controller.hpp"

namespace mvz {
    struct GlobalUbo {
        glm::mat4 projectionView{1.f};
        glm::vec4 ambientLightColor{1.f, 1.f, 1.f, .02f}; // w is intensity
        glm::vec3 lightPosition{-1.f};
        alignas(16)glm::vec4 lightColor{1.f}; // w is light intensity
    };

    MainApp::MainApp() {
        globalPool = MvzDescriptorPool::Builder(mvzDevice)
                .setMaxSets(MvzSwapChain::MAX_FRAMES_IN_FLIGHT)
                .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, MvzSwapChain::MAX_FRAMES_IN_FLIGHT)
                .build();
        loadGameObjects();
    }

    MainApp::~MainApp() {
    }

    void MainApp::run() {
        std::vector<std::unique_ptr<MvzBuffer> > uboBuffers(MvzSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < uboBuffers.size(); i++) {
            uboBuffers[i] = std::make_unique<MvzBuffer>(
                mvzDevice,
                sizeof(GlobalUbo),
                1,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
            );
            uboBuffers[i]->map();
        }

        auto globalSetLayout = MvzDescriptorSetLayout::Builder(mvzDevice)
                .addBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
                .build();

        std::vector<VkDescriptorSet> globalDescriptorSets(MvzSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < globalDescriptorSets.size(); i++) {
            auto bufferInfo = uboBuffers[i]->descriptorInfo();
            MvzDescriptorWriter(*globalSetLayout, *globalPool)
                    .writeBuffer(0, &bufferInfo)
                    .build(globalDescriptorSets[i]);
        }

        SimpleRenderSystem simpleRenderSystem{
            mvzDevice, mvzRenderer.getSwapChainRenderPass(), globalSetLayout->getDescriptorSetLayout()
        };
        MvzCamera camera{};
        camera.setViewTarget(glm::vec3{-1.f, -2.f, 20.f}, glm::vec3{.0f, .0f, 2.5f});

        auto viewerObject = MvzGameObject::createGameObject();
        viewerObject.transform.translation.z = -2.5f;
        KeyboardMovementController cameraController{};

        auto currentTime = std::chrono::high_resolution_clock::now();

        while (!mvzWindow.shouldClose()) {
            glfwPollEvents();

            auto newTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
            currentTime = newTime;

            cameraController.moveInPlaneXZ(mvzWindow.getGLFWwindow(), frameTime, viewerObject);
            camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = mvzRenderer.getAspectRatio();
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, .1f, 100.f);

            if (auto commandBuffer = mvzRenderer.beginFrame()) {
                int frameIndex = mvzRenderer.getFrameIndex();
                FrameInfo frameInfo{
                    frameIndex,
                    frameTime,
                    commandBuffer,
                    camera,
                    globalDescriptorSets[frameIndex],
                    gameObjects
                };
                // update
                GlobalUbo ubo{};
                ubo.projectionView = camera.getProjection() * camera.getView();
                uboBuffers[frameIndex]->writeToBuffer(&ubo);
                uboBuffers[frameIndex]->flush();

                // render
                mvzRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(frameInfo);
                mvzRenderer.endSwapChainRenderPass(commandBuffer);
                mvzRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(mvzDevice.device());
    }

    void MainApp::loadGameObjects() {
        std::shared_ptr<MvzModel> mvzModel = MvzModel::createModelFromFile(mvzDevice, "../models/flat_vase.obj");
        auto flatVase = MvzGameObject::createGameObject();
        flatVase.model = mvzModel;
        flatVase.transform.translation = {-.5f, .5f, 0.f};
        flatVase.transform.scale = glm::vec3{3.f, 1.5f, 3.f};
        gameObjects.emplace(flatVase.getId(), std::move(flatVase));

        mvzModel = MvzModel::createModelFromFile(mvzDevice, "../models/smooth_vase.obj");
        auto smoothVase = MvzGameObject::createGameObject();
        smoothVase.model = mvzModel;
        smoothVase.transform.translation = {.5f, .5f, 0.f};
        smoothVase.transform.scale = glm::vec3{3.f, 1.5f, 3.f};
        gameObjects.emplace(smoothVase.getId(), std::move(smoothVase));

        mvzModel = MvzModel::createModelFromFile(mvzDevice, "../models/quad.obj");
        auto floor = MvzGameObject::createGameObject();
        floor.model = mvzModel;
        floor.transform.translation = {0.f, .5f, 0.f};
        floor.transform.scale = glm::vec3{3.f, 1.f, 3.f};
        gameObjects.emplace(floor.getId(), std::move(floor));
    }
}
