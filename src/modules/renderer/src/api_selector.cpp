#include "api_selector.hpp"
#include "vulkan_renderer.hpp"

std::unique_ptr<IRenderer> ApiSelector::createRenderer(RendererApi api) {
    switch (api) {
        case RendererApi::Vulkan:
            return std::make_unique<VulkanRenderer>(extensions, window);
        default:
            throw std::runtime_error("Unknown renderer api");
    }
}