#include "command.hpp"

namespace Tomulo {
    CommandPool::CommandPool(Tomulo::Device* device) : device{device} {
        Device::QueueFamilyIndices queueFamilyIndices = device->findQueueFamilies(device->physical());
        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
        if(vkCreateCommandPool(device->logical(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create command pool!");
        }
    }
    CommandPool::~CommandPool() {
        vkDestroyCommandPool(device->logical(), commandPool, nullptr);
    }

    VkCommandPool CommandPool::get() {
        return commandPool;
    }

    CommandBuffer::CommandBuffer(Tomulo::Device* device, Tomulo::SwapChain* swapchain, Tomulo::Renderpass* renderpass, Tomulo::Pipeline* pipeline, Tomulo::Framebuffers* framebuffers, Tomulo::CommandPool* commandpool) : device{device}, swapchain{swapchain}, renderpass{renderpass}, pipeline{pipeline}, framebuffers{framebuffers}, commandpool{commandpool} {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandpool->get();
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;
        if(vkAllocateCommandBuffers(device->logical(), &allocInfo, &commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate command buffer!");
        }
    }
    CommandBuffer::~CommandBuffer() {

    }
    VkCommandBuffer CommandBuffer::get() {
        return commandBuffer;
    }
    void CommandBuffer::reset() {
        vkResetCommandBuffer(commandBuffer, 0);
    }
    void CommandBuffer::record(uint32_t imageIndex) {
        VkExtent2D swapchainExtent = swapchain->getSwapchainExtent();
        std::vector<VkFramebuffer> swapchainFramebuffers = framebuffers->get();
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("Failed to begin recording command buffer!");
        }
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = renderpass->get();
        renderPassInfo.framebuffer = swapchainFramebuffers[imageIndex];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapchainExtent;

        VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->get());

            VkViewport viewport{};
            viewport.x = 0.0f;
            viewport.y = 0.0f;
            viewport.width = (float) swapchainExtent.width;
            viewport.height = (float) swapchainExtent.height;
            viewport.minDepth = 0.0f;
            viewport.maxDepth = 1.0f;
            vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

            VkRect2D scissor{};
            scissor.offset = {0, 0};
            scissor.extent = swapchainExtent;
            vkCmdSetScissor(commandBuffer, 0, 1, &scissor);            

            vkCmdDraw(commandBuffer, 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffer);

        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("Failed to record command buffer!");
        }
    }
}