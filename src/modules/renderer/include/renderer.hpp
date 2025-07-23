#ifndef RENDERER_HPP
#define RENDERER_HPP

class Window;

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void init(Window& window) = 0;
    virtual void drawFrame() = 0;
    virtual void cleanup() = 0;
};

#endif // RENDERER_HPP
