#ifndef ENGINE_RUNTIME_H
#define ENGINE_RUNTIME_H

#include <memory>

class Window;

class Runtime
{
  public:
    Runtime();
    ~Runtime();

    void run();

  private:
    std::unique_ptr<Window> window;
};

#endif // ENGINE_RUNTIME_H
