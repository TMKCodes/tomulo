#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <cstring>

#include "debugger.hpp"
#include "window.hpp"
#include "device.hpp"
#include "swapchain.hpp"
#include "view.hpp"



namespace tomulo {
    class Renderer {
        public:
            Renderer(int height, int width, std::string name, bool fullscreen);
            ~Renderer();
            void printExtensions();
            bool shouldClose();
        private:
            tomulo::Window* window;
            tomulo::DebugMessenger* debugger;
            tomulo::Device* device;
            tomulo::SwapChain* swapchain;
            tomulo::View* imageView;
            VkInstance instance;
            VkSurfaceKHR surface;

            void createSurface();
            void createValidation();
            bool checkValidationLayerSupport();
            void createInstance();
            std::vector<const char*> getRequiredExtensions();
    };
}