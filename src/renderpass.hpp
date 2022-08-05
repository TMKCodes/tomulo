#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "device.hpp"

namespace Tomulo {
    class Renderpass {
        public:
            Renderpass(Tomulo::Device* device, VkFormat imageFormat);
            ~Renderpass();
        private:
            Tomulo::Device* device;
            VkRenderPass renderpass;
    };
}