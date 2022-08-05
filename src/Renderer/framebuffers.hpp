#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

#include "device.hpp"
#include "swapchain.hpp"
#include "views.hpp"
#include "renderpass.hpp"

namespace Tomulo {
    class Framebuffers {
        public:
            Framebuffers(Tomulo::Device* device, Tomulo::Renderpass* renderpass, Tomulo::SwapChain* swapchain, Tomulo::Views* view);
            ~Framebuffers();
            std::vector<VkFramebuffer> get();
        private:
            Tomulo::Device* device;
            Tomulo::Renderpass* renderpass;
            Tomulo::SwapChain* swapchain; 
            Tomulo::Views* views;
            std::vector<VkFramebuffer> framebuffers;

    };
}