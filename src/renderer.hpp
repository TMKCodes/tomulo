#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include <cstring>

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
            //tomulo::Validation* validation;
            tomulo::Device* device;
            tomulo::SwapChain* swapchain;
            VkInstance instance;
            VkSurfaceKHR surface;
            VkDebugUtilsMessengerEXT debugMessenger;

            void createSurface();
            void createValidation();
            bool checkValidationLayerSupport();
            void createInstance();
            std::vector<const char*> getRequiredExtensions();
            const std::vector<const char*> validationLayers = {
                "VK_LAYER_KHRONOS_validation"
            };
            
    };
}