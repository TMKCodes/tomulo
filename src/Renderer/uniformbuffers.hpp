#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#include "device.hpp"
#include "buffer.hpp"

namespace Tomulo {
    
    class UniformBuffers {
        public:
            UniformBuffers(Tomulo::Device* device);
            ~UniformBuffers();
            void UpdateUniformBuffer(VkExtent2D swapchainExtent, uint32_t currentFrame);
            struct UniformBufferObject {
                glm::mat4 model;
                glm::mat4 view;
                glm::mat4 proj;
            };
        private:
            Tomulo::Device* device;
            std::vector<Tomulo::Buffer*> uniformBuffers;
    };
}