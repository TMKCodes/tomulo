#include "synobjects.hpp"

namespace Tomulo {
    SynObjects::SynObjects(Tomulo::Device* device) : device{device} {
        VkSemaphoreCreateInfo semaphoreInfo{};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
        if(vkCreateSemaphore(device->logical(), &semaphoreInfo, nullptr, &imageAvailableSemaphore) != VK_SUCCESS ||
            vkCreateSemaphore(device->logical(), &semaphoreInfo, nullptr, &renderFinishedSemaphore) != VK_SUCCESS ||
            vkCreateFence(device->logical(), &fenceInfo, nullptr, &inFlightFence) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create semaphores!");
        }
    }
    SynObjects::~SynObjects() {
        vkDestroySemaphore(device->logical(), imageAvailableSemaphore, nullptr);
        vkDestroySemaphore(device->logical(), renderFinishedSemaphore, nullptr);
        vkDestroyFence(device->logical(), inFlightFence, nullptr);
    }
}