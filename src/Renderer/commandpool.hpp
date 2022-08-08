#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

#include "device.hpp"


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
}