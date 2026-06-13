#include "main_app.hpp"
#include <stdexcept>

#include "simple_render_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace mvz {
    MainApp::MainApp() {
        loadGameObjects();
    }

    MainApp::~MainApp() {
    }

    void MainApp::run() {
        SimpleRenderSystem simpleRenderSystem{mvzDevice, mvzRenderer.getSwapChainRenderPass()};
        while (!mvzWindow.shouldClose()) {
            glfwPollEvents();
            if (auto commandBuffer = mvzRenderer.beginFrame()) {
                mvzRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
                mvzRenderer.endSwapChainRenderPass(commandBuffer);
                mvzRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(mvzDevice.device());
    }

    void MainApp::loadGameObjects() {
        std::vector<MvzModel::Vertex> vertices{
            {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        };

        auto mvzModel = std::make_shared<MvzModel>(mvzDevice, vertices);
        auto triangle = MvzGameObject::createGameObject();
        triangle.model = mvzModel;
        triangle.color = {.1f, 0.8f, 0.1f};
        triangle.transform2d.translation.x = .2f;
        triangle.transform2d.scale = {2.f, .5f};
        triangle.transform2d.rotation = .25f * glm::two_pi<float>();

        gameObjects.push_back(std::move(triangle));
    }
}
