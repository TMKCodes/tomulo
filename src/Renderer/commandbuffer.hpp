#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

#include "device.hpp"
#include "swapchain.hpp"
#include "renderpass.hpp"
#include "pipeline.hpp"
#include "framebuffers.hpp"
#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"

namespace Tomulo {
    class CommandBuffers {
        public:
            CommandBuffers(Tomulo::Device* device, Tomulo::SwapChain* swapchain, Tomulo::Renderpass* renderpass, Tomulo::Pipeline* pipeline, Tomulo::Framebuffers* framebuffers, Tomulo::CommandPool* commandpool);
            ~CommandBuffers();
            VkCommandBuffer get(uint32_t currentFrame);
            void reset(uint32_t currentFrame);
            void record(std::vector<VkFramebuffer> swapchainFrameBuffers, VkExtent2D swapchainExtent, Tomulo::VertexBuffer* vertexBuffer, Tomulo::IndexBuffer* indexBuffer, uint32_t imageIndex, uint32_t currentFrame);
        private:
            Tomulo::Device* device;
            Tomulo::SwapChain* swapchain;
            Tomulo::Renderpass* renderpass;
            Tomulo::Pipeline* pipeline;
            Tomulo::Framebuffers* framebuffers;
            Tomulo::CommandPool* commandpool;
            std::vector<VkCommandBuffer> commandBuffers;
    };
}