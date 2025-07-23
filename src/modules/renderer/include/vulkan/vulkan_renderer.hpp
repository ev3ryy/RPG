#ifndef VULKAN_RENDERER_HPP
#define VULKAN_RENDERER_HPP

#include <window.hpp>
#include <vulkan/vulkan.h>
#include <vector>
#include <string>

class VulkanRenderer : public Renderer {
public:
    VulkanRenderer(const std::vector<std::string>& extensions, Window& window);
    ~VulkanRenderer() override;

    void init(Window& window) override;
    void drawFrame() override;
    void cleanup() override;

private:
    // vulkan objects
    VkInstance instance{};
    VkPhysicalDevice physicalDevice{};
    VkDevice device{};
    VkQueue graphicsQueue{};
    VkSurfaceKHR surface{};
    VkSwapchainKHR swapChain{};
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    // methods for initialization
    void createInstance();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSurface(Window& window);
    void createSwapChain(Window& window);
    void createRenderPass();    // added on July 20, 2025
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
};

#endif // VULKAN_RENDERER_HPP
