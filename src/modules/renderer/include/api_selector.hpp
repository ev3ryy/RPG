#ifndef API_SELECTOR_HPP
#define API_SELECTOR_HPP

#include "renderer.hpp"
#include <memory>
#include <string>

enum class RendererApi {
    Vulkan,
    // ...,
};

class ApiSelector {
public:
    static std::unique_ptr<IRenderer> createRenderer(RendererApi api);
};

#endif // API_SELECTOR_HPP