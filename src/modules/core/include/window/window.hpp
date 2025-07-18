#ifndef RENDERER_WINDOW_H
#define RENDERER_WINDOW_H

#include <cstdint>

struct GLFWwindow;

class Window
{
  public:
    Window(const uint32_t width, const uint32_t height, const char *title);
    Window() = delete;

    ~Window();

    void pollEvents();

    GLFWwindow *getWindow() const
    {
        return window;
    }

    bool isFramebufferResized() const
    {
        return framebufferResized;
    }

    bool isWindowShouldClose();

  private:
    void init(const uint32_t width, const uint32_t height, const char *title);
    static void framebufferResizeCallback(GLFWwindow *glfwWindow, int width, int height);

    GLFWwindow *window;
    bool framebufferResized;
};

#endif // RENDERER_WINDOW_H
