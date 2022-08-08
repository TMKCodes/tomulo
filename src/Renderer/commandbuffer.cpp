#include "commandbuffer.hpp"

namespace Tomulo {
    CommandBuffers::CommandBuffers(Tomulo::Device* device, Tomulo::SwapChain* swapchain, Tomulo::Renderpass* renderpass, Tomulo::Pipeline* pipeline, Tomulo::Framebuffers* framebuffers, Tomulo::CommandPool* commandpool) : device{device}, swapchain{swapchain}, renderpass{renderpass}, pipeline{pipeline}, framebuffers{framebuffers}, commandpool{commandpool} {
        commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandpool->get();
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = (uint32_t) commandBuffers.size();
        if(vkAllocateCommandBuffers(device->logical(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate command buffer!");
        }
    }
    CommandBuffers::~CommandBuffers() {

    }
    VkCommandBuffer CommandBuffers::get(uint32_t currentFrame) {
        return commandBuffers[currentFrame];
    }
    void CommandBuffers::reset(uint32_t currentFrame) {
        vkResetCommandBuffer(commandBuffers[currentFrame], 0);
    }
    void CommandBuffers::record(std::vector<VkFramebuffer> swapchainFrameBuffers, VkExtent2D swapchainExtent, Tomulo::VertexBuffer* vertexBuffer, Tomulo::IndexBuffer* indexBuffer, uint32_t imageIndex, uint32_t currentFrame) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffers[currentFrame], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("Failed to begin recording command buffer!");
        }
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = renderpass->get();
        renderPassInfo.framebuffer = swapchainFrameBuffers[imageIndex];
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapchainExtent;

        VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        vkCmdBeginRenderPass(commandBuffers[currentFrame], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            vkCmdBindPipeline(commandBuffers[currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->get());

            VkViewport viewport{};
            viewport.x = 0.0f;
            viewport.y = 0.0f;
            viewport.width = (float) swapchainExtent.width;
            viewport.height = (float) swapchainExtent.height;
            viewport.minDepth = 0.0f;
            viewport.maxDepth = 1.0f;
            vkCmdSetViewport(commandBuffers[currentFrame], 0, 1, &viewport);

            VkRect2D scissor{};
            scissor.offset = {0, 0};
            scissor.extent = swapchainExtent;
            vkCmdSetScissor(commandBuffers[currentFrame], 0, 1, &scissor);            

            VkBuffer vertexBuffers[] = {vertexBuffer->get()};
            VkDeviceSize offsets[] = {0};
            vkCmdBindVertexBuffers(commandBuffers[currentFrame], 0, 1, vertexBuffers, offsets);
            // Remove index buffer binding and uncomment vkCmdDraw to draw unindexed.
            vkCmdBindIndexBuffer(commandBuffers[currentFrame], indexBuffer->get(), 0, VK_INDEX_TYPE_UINT16);
            
            vkCmdDraw(commandBuffers[currentFrame], static_cast<uint32_t>(vertexBuffer->vertices.size()), 1, 0, 0);
            vkCmdDrawIndexed(commandBuffers[currentFrame], static_cast<uint32_t>(indexBuffer->indices.size()), 1, 0, 0, 0);
        vkCmdEndRenderPass(commandBuffers[currentFrame]);

        if (vkEndCommandBuffer(commandBuffers[currentFrame]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to record command buffer!");
        }
    }
}