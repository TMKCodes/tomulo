#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <cstring>

#include "window.hpp"
#include "device.hpp"


namespace tomulo {
    class Renderer {
        public:
            Renderer(int height, int width, std::string name, bool fullscreen);
            ~Renderer();
            void printExtensions();
            bool shouldClose();
        private:
            tomulo::Window* window;
            tomulo::Device* device;
            VkInstance instance;
            VkSurfaceKHR surface;

            void createSurface();
            void createInstance();
            std::vector<const char*> getRequiredExtensions();
            
    };
}