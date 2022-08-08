#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

#include "device.hpp"

namespace Tomulo {
    class SynObjects {
        public:
            SynObjects(Tomulo::Device* device);
            ~SynObjects();
            std::vector<VkSemaphore> imageAvailableSemaphores;
            std::vector<VkSemaphore> renderFinishedSemaphores;
            std::vector<VkFence> inFlightFences;
        private:
            Tomulo::Device* device;
    };
}