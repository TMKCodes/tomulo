#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "device.hpp"
#include "swapchain.hpp"
#include "views.hpp"
#include "renderpass.hpp"
#include "pipeline.hpp"
#include "framebuffers.hpp"

namespace Tomulo {
    class CommandPool {
        public:
            CommandPool(Tomulo::Device* device);
            ~CommandPool();
            VkCommandPool get();
        private:
            Tomulo::Device* device;
            VkCommandPool commandPool;
    };
    class CommandBuffer {
        public:
            CommandBuffer(Tomulo::Device* device, Tomulo::SwapChain* swapchain, Tomulo::Renderpass* renderpass, Tomulo::Pipeline* pipeline, Tomulo::Framebuffers* framebuffers, Tomulo::CommandPool* commandpool);
            ~CommandBuffer();
            VkCommandBuffer get();
            void reset();
            void record(uint32_t imageIndex);
        private:
            Tomulo::Device* device;
            Tomulo::SwapChain* swapchain;
            Tomulo::Renderpass* renderpass;
            Tomulo::Pipeline* pipeline;
            Tomulo::Framebuffers* framebuffers;
            Tomulo::CommandPool* commandpool;
            VkCommandBuffer commandBuffer;
    };
}