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
#include "views.hpp"
#include "renderpass.hpp"
#include "pipeline.hpp"
#include "framebuffers.hpp"
#include "command.hpp"
#include "synobjects.hpp"



namespace Tomulo {
    class Renderer {
        public:
            Renderer(int height, int width, std::string name, bool fullscreen);
            ~Renderer();
            void printExtensions();
            bool shouldClose();
            void drawFrame();
        private:
            Tomulo::Window* window;
            Tomulo::DebugMessenger* debugger;
            Tomulo::Device* device;
            Tomulo::SwapChain* swapchain;
            Tomulo::Views* imageViews;
            Tomulo::Renderpass* renderpass;
            Tomulo::Pipeline* pipeline;
            Tomulo::Framebuffers* framebuffers;
            Tomulo::CommandPool* commandpool;
            Tomulo::CommandBuffer* commandbuffer;
            Tomulo::SynObjects* synobjects;
            VkInstance instance;
            VkSurfaceKHR surface;

            void createSurface();
            void createValidation();
            bool checkValidationLayerSupport();
            void createInstance();
            std::vector<const char*> getRequiredExtensions();
    };
}