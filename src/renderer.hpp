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
#include "renderpass.hpp"
#include "pipeline.hpp"



namespace Tomulo {
    class Renderer {
        public:
            Renderer(int height, int width, std::string name, bool fullscreen);
            ~Renderer();
            void printExtensions();
            bool shouldClose();
        private:
            Tomulo::Window* window;
            Tomulo::DebugMessenger* debugger;
            Tomulo::Device* device;
            Tomulo::SwapChain* swapchain;
            Tomulo::View* imageView;
            Tomulo::Renderpass* renderpass;
            Tomulo::Pipeline* pipeline;
            VkInstance instance;
            VkSurfaceKHR surface;

            void createSurface();
            void createValidation();
            bool checkValidationLayerSupport();
            void createInstance();
            std::vector<const char*> getRequiredExtensions();
    };
}