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
        glm::vec3 lightDirection = glm::normalize(glm::vec3{1.f, -3.f, -1.f});
    };

    MainApp::MainApp() {
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

        SimpleRenderSystem simpleRenderSystem{mvzDevice, mvzRenderer.getSwapChainRenderPass()};
        MvzCamera camera{};
        camera.setViewTarget(glm::vec3{-1.f, -2.f, 20.f}, glm::vec3{.0f, .0f, 2.5f});

        auto viewerObject = MvzGameObject::createGameObject();
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
                    frameTime, commandBuffer, camera
                };
                // update
                GlobalUbo ubo{};
                ubo.projectionView = camera.getProjection() * camera.getView();
                uboBuffers[frameIndex]->writeToBuffer(&ubo);
                uboBuffers[frameIndex]->flush();

                // render
                mvzRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(frameInfo, gameObjects);
                mvzRenderer.endSwapChainRenderPass(commandBuffer);
                mvzRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(mvzDevice.device());
    }

    void MainApp::loadGameObjects() {
        std::shared_ptr<MvzModel> mvzModel = MvzModel::createModelFromFile(mvzDevice, "../models/flat_vase.obj");
        auto gameObj = MvzGameObject::createGameObject();
        gameObj.model = mvzModel;
        gameObj.transform.translation = {.0f, .5f, 2.5f};
        gameObj.transform.scale = glm::vec3{3.f};
        gameObjects.push_back(gameObj);
    }
}
