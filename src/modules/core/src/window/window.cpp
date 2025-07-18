#include "window/window.hpp"
#include "logs.hpp"

#include <GLFW/glfw3.h>

Window::Window(const uint32_t width, const uint32_t height, const char *title)
{
    init(width, height, title);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();

    LOG_INFO("glfw terminate");
}

void Window::init(const uint32_t width, const uint32_t height, const char *title)
{
    if (!glfwInit())
    {
        LOG_CRITICAL("failed to initialize glfw");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        LOG_CRITICAL("failed to create window");
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);

    LOG_INFO("window: initialized!");
}

void Window::framebufferResizeCallback(GLFWwindow *glfwWindow, int width, int height)
{
    auto wnd = reinterpret_cast<Window *>(glfwGetWindowUserPointer(glfwWindow));
    if (wnd)
    {
        wnd->framebufferResized = true;
    }
}

void Window::pollEvents()
{
    glfwPollEvents();
}

bool Window::isWindowShouldClose()
{
    return glfwWindowShouldClose(window);
}