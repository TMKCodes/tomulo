#include "descriptors.hpp"

namespace Tomulo {
    Descriptors::Descriptors(Tomulo::Device* device, uint32_t binding, uint32_t count) : device{device} {
        VkDescriptorSetLayoutBinding uboLayoutBinding{};
        uboLayoutBinding.binding = binding;
        uboLayoutBinding.descriptorCount = count;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.pImmutableSamplers = nullptr;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = 1;
        layoutInfo.pBindings = &uboLayoutBinding;

        if (vkCreateDescriptorSetLayout(device->logical(), &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create descriptor set layout!");
        }
    }
    Descriptors::~Descriptors() {
        vkDestroyDescriptorSetLayout(device->logical(), descriptorSetLayout, nullptr);
    }

    VkDescriptorSetLayout Descriptors::get() {
        return descriptorSetLayout;
    }
}