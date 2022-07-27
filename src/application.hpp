#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include "renderer.hpp"

namespace tomulo {
    class Application {
        public:
            Application();
            ~Application();

            void run();
        private:
            tomulo::Renderer* renderer;
    };
}