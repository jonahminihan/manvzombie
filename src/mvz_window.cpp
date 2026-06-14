#include "mvz_window.hpp"

#include <utility>
#include <stdexcept>

namespace mvz {
    MvzWindow::MvzWindow(int width, int height, std::string title) : width(width), height(height),
                                                                     windowName(std::move(title)) {
        initWindow();
    }

    MvzWindow::~MvzWindow() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void MvzWindow::initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
    }

    bool MvzWindow::shouldClose() { return glfwWindowShouldClose(window); }

    void MvzWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void MvzWindow::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
        auto mvzWindow = reinterpret_cast<MvzWindow *>(glfwGetWindowUserPointer(window));
        mvzWindow->framebufferResized = true;
        mvzWindow->width = width;
        mvzWindow->height = height;
    }
}
