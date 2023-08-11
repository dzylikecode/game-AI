#pragma once
#include "utils/type.h"

class BaseApplication {
 public:
  BaseApplication(const String& applicationTitle = "", const int width = 800,
                  const int height = 600);
  virtual ~BaseApplication();

  void run();

  virtual void init();
  virtual bool update();
  virtual void shutdown();

 private:
  String m_applicationTitle;
  int m_width;
  int m_height;

 private:
  bool setup();
  void close();
  void main();
};
