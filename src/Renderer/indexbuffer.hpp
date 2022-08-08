#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "buffer.hpp"
#include "commandpool.hpp"

namespace Tomulo {
    
    class IndexBuffer {
        public:
            IndexBuffer(Tomulo::Device* device, Tomulo::CommandPool* commandpool);
            ~IndexBuffer();
            VkBuffer get();
            std::vector<uint16_t> indices = {
                0, 1, 2, 2, 3, 0
            };
        private:
            Tomulo::CommandPool* commandpool;
            Tomulo::Device* device;
            Tomulo::Buffer* indexBuffer;
            Tomulo::Buffer* stagingBuffer;
            VkDeviceSize bufferSize;
            void copyBuffer();
            
    };
}