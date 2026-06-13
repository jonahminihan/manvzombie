#pragma once
#include "mvz_window.hpp"
#include "mvz_device.hpp"
#include "mvz_game_object.hpp"
#include "mvz_renderer.hpp"

#include <memory>
#include <vector>

namespace mvz {
    class MainApp {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        MainApp();

        ~MainApp();

        MainApp(const MainApp &) = delete;

        MainApp &operator=(const MainApp &) = delete;

        void run();

    private:
        void loadGameObjects();

        MvzWindow mvzWindow{WIDTH, HEIGHT, "Man V Zombie"};
        MvzDevice mvzDevice{mvzWindow};
        MvzRenderer mvzRenderer{mvzWindow, mvzDevice};
        std::vector<MvzGameObject> gameObjects;
    };
}
