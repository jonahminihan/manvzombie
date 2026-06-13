#include "main_app.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
    mvz::MainApp app{};

    try {
        app.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


