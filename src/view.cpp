#include "view.hpp"


namespace Tomulo {
    View::View(Tomulo::Device* device, std::vector<VkImage> images, VkFormat imageFormat) : device{device} {
        views.resize(images.size());
        for(size_t i = 0; i < images.size(); i++) {
            VkImageViewCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            createInfo.image = images[i];
            createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            createInfo.format = imageFormat;
            createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            createInfo.subresourceRange.baseMipLevel = 0;
            createInfo.subresourceRange.levelCount = 1;
            createInfo.subresourceRange.baseArrayLayer = 0;
            createInfo.subresourceRange.layerCount = 1;
            if(vkCreateImageView(device->logical(), &createInfo, nullptr, &views[i]) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create image views!");
            }
        }
    }
    View::~View() {
        for(auto view : views) {
            vkDestroyImageView(device->logical(), view, nullptr);
        }
    }
}