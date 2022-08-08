#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <array>
#include <vector>

#include "device.hpp"

namespace Tomulo {
    
    class Buffer {
        public:
            Buffer(Tomulo::Device* device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
            ~Buffer();
            VkBuffer getBuffer();
            VkDeviceMemory getMemory();
            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        private:
            Tomulo::Device* device;
            VkBuffer buffer;
            VkDeviceMemory bufferMemory;
    };
}