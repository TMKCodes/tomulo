#include "commandpool.hpp"

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
}