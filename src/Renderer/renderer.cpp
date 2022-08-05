#include "renderer.hpp"


namespace Tomulo {
    Renderer::Renderer(int height, int width, std::string name, bool fullscreen) {
        window = new Tomulo::Window(height, width, name, fullscreen);
        createInstance();
        debugger = new Tomulo::DebugMessenger(instance);
        createSurface();
        device = new Tomulo::Device(instance, surface);
        swapchain = new Tomulo::SwapChain(window, device, surface);
        imageViews = new Tomulo::Views(device, swapchain->getSwapchainImages(), swapchain->getSwapchainImageFormat()); 
        renderpass = new Tomulo::Renderpass(device, swapchain->getSwapchainImageFormat());
        pipeline = new Tomulo::Pipeline(device, renderpass);
        framebuffers = new Tomulo::Framebuffers(device, renderpass, swapchain, imageViews);
    }
    Renderer::~Renderer() {
        delete pipeline;
        delete swapchain;
        delete device;
        delete debugger;
        vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
        delete window;
    }
    void Renderer::createInstance() {
        if(enableValidationLayers && !debugger->checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Lollero";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Tomulo";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        if(enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
            debugger->populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create instance!");
        }
    }
    void Renderer::createSurface() {
        if(glfwCreateWindowSurface(instance, window->get(), nullptr, &surface) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create window surface!");
        }
    }
    void Renderer::printExtensions() {
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::cout << "Available extensions:\n";
        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << std::endl;
        }
    }
    std::vector<const char*> Renderer::getRequiredExtensions() {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
        if(enableValidationLayers) {
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }
        return extensions;
    }
    bool Renderer::shouldClose() {
        return window->shouldClose();
    }
}