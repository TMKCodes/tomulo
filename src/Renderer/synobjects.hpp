#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "device.hpp"

namespace Tomulo {
    class SynObjects {
        public:
            SynObjects(Tomulo::Device* device);
            ~SynObjects();
            VkSemaphore imageAvailableSemaphore;
            VkSemaphore renderFinishedSemaphore;
            VkFence inFlightFence;
        private:
            Tomulo::Device* device;
    };
}