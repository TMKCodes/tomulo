#include "indexbuffer.hpp"

namespace Tomulo {
    IndexBuffer::IndexBuffer(Tomulo::Device* device, Tomulo::CommandPool* commandpool) : device{device}, commandpool{commandpool} {
        bufferSize = sizeof(indices[0]) * indices.size();

        stagingBuffer = new Tomulo::Buffer(device, bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        void* data;
        vkMapMemory(device->logical(), stagingBuffer->getMemory(), 0, bufferSize, 0, &data);
        memcpy(data, indices.data(), (size_t) bufferSize);
        vkUnmapMemory(device->logical(), stagingBuffer->getMemory());

        indexBuffer = new Tomulo::Buffer(device, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        copyBuffer();

        vkDestroyBuffer(device->logical(), stagingBuffer->getBuffer(), nullptr);
        vkFreeMemory(device->logical(), stagingBuffer->getMemory(), nullptr);
    }
    IndexBuffer::~IndexBuffer() {
        delete indexBuffer;
        delete stagingBuffer;
    }
    VkBuffer IndexBuffer::get() {
        return indexBuffer->getBuffer();
    }
    void IndexBuffer::copyBuffer() {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandpool->get();
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(device->logical(), &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        vkBeginCommandBuffer(commandBuffer, &beginInfo);

        VkBufferCopy copyRegion{};
        copyRegion.srcOffset = 0;
        copyRegion.dstOffset = 0;
        copyRegion.size = bufferSize;
        vkCmdCopyBuffer(commandBuffer, stagingBuffer->getBuffer(), indexBuffer->getBuffer(), 1, &copyRegion);

        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(device->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(device->graphicsQueue);
        vkFreeCommandBuffers(device->logical(), commandpool->get(), 1, &commandBuffer);
    }
}