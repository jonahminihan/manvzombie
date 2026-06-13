#pragma once

#ifndef MANVZOMBIE_MVZ_WINDOW_HPP
#define MANVZOMBIE_MVZ_WINDOW_HPP
#include <string>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#endif //MANVZOMBIE_MVZ_WINDOW_HPP

namespace mvz {
    class MvzWindow {
    public:
        MvzWindow(int width, int height, std::string title);

        ~MvzWindow();

        MvzWindow(const MvzWindow &) = delete;

        MvzWindow &operator=(const MvzWindow &) = delete;

        bool shouldClose();

        VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; };
        bool wasWindowResized() { return framebufferResized; };
        void resetWindowResizedFlag() { framebufferResized = false; };

        void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

    private:
        static void framebufferResizeCallback(GLFWwindow *window, int width, int height);

        void initWindow();

        int width;
        int height;
        bool framebufferResized = false;

        std::string windowName;
        GLFWwindow *window;
    };
}
