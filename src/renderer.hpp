#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <cstring>

#include "validation.hpp"
#include "window.hpp"
#include "device.hpp"
#include "swapchain.hpp"


namespace tomulo {
    class Renderer {
        public:
            Renderer(int height, int width, std::string name, bool fullscreen);
            ~Renderer();
            void printExtensions();
            bool shouldClose();
        private:
            tomulo::Window* window;
            tomulo::Validation* validation;
            tomulo::Device* device;
            tomulo::SwapChain* swapchain;
            VkInstance instance;
            VkSurfaceKHR surface;

            void createSurface();
            void createInstance();
            std::vector<const char*> getRequiredExtensions();
            
    };
}