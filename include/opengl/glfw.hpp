#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <functional>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <string>

enum Type { CORE, COMPAT };

namespace GLFW {
class Init {
private:
  Init(int majar_version = 3, int minor_versio = 3, Type type = CORE);

public:
  static Init &getInstance(int majar_version = 3, int minor_versio = 3,
                           Type type = CORE);
  ~Init();
};

class WindowWrapper {
private:
  int m_width;
  int m_height;
  Type m_type;
  std::string m_title;
  std::string m_version;

  std::shared_ptr<GLFWwindow> window;

public:
  WindowWrapper(int width = 800, int height = 600,
                std::string &&title = "GLFW Window", int major_version = 3,
                int minor_version = 3, Type type = CORE);
  ~WindowWrapper();
  // Create a new window
  static std::shared_ptr<WindowWrapper>
  createWindow(int width = 800, int height = 600,
               std::string &&title = "GLFW Window", int major_version = 3,
               int minor_version = 3, Type type = CORE);
  // Get the raw pointer to the GLFWwindow
  GLFWwindow *get() const;
  // Judge if the window should be closed
  bool shouldClose() const;
  // Make the window's context current
  void makeContextCurrent() const;
  // Swap the front and back buffers of the window
  void swapBuffers() const;
  // Poll for and process events
  void pollEvents() const;

  /**************** < Set Function And Method > ****************/
  void setKeyCallback(GLFWkeyfun callback);
  void setMouseButtonCallback(GLFWmousebuttonfun callback);
  void setCursorPosCallback(GLFWcursorposfun callback);
  void setScrollCallback(GLFWscrollfun callback);
  void setFramebufferSizeCallback(GLFWframebuffersizefun callback);
  void setWindowCloseCallback(GLFWwindowclosefun callback);
  void setWindowRefreshCallback(GLFWwindowrefreshfun callback);
  void setWindowFocusCallback(GLFWwindowfocusfun callback);
  void setWindowIconifyCallback(GLFWwindowiconifyfun callback);
  void setWindowMaximizeCallback(GLFWwindowmaximizefun callback);
  void setWindowContentScaleCallback(GLFWwindowcontentscalefun callback);
  void setWindowPosCallback(GLFWwindowposfun callback);
  void setWindowSizeCallback(GLFWwindowsizefun callback);
  void setWindowAspectRatioCallback(GLFWwindowsizefun callback);
  /**************** < Set Function And Method > ****************/

  /**************** < Get Function And Method > ****************/
  int getWidth() const;
  int getHeight() const;
  std::string getVersion() const;
  std::string getType() const;
  std::string getTitle() const;
  /**************** < Get Function And Method > ****************/

  /**************** <         MainLoop        > ****************/
  void mainLoop(std::function<void()> callback) const;
  /**************** <         MainLoop        > ****************/
};
} // namespace GLFW