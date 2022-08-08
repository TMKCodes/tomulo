#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
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
#include "vertexbuffer.hpp"
#include "synobjects.hpp"



namespace Tomulo {
    class Renderer {
        public:
            Renderer(int height, int width, std::string name, bool fullscreen);
            ~Renderer();
            void printExtensions();
            bool shouldClose();
            void drawFrame();
            void recreateSwapchain();
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
            Tomulo::VertexBuffer* vertexbuffer;
            Tomulo::CommandBuffers* commandbuffers;
            Tomulo::SynObjects* synobjects;
            VkInstance instance;
            VkSurfaceKHR surface;
            uint32_t currentFrame = 0;

            void createSurface();
            void createValidation();
            bool checkValidationLayerSupport();
            void createInstance();
            std::vector<const char*> getRequiredExtensions();
    };
}