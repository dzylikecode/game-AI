#include <exception>
#include <iostream>

#include "App/SandboxApplication.h"

class TestApp : public SandboxApplication {
 public:
  TestApp(const String& appName) : SandboxApplication(appName) {}
  virtual ~TestApp() {}

  void setup() override {
    SandboxApplication::setup();
    createSandbox("Sandbox.lua");
  }
};

int main(int argc, char** argv) {
#ifdef MY_OGRE_CONFIG_DIR
  //! [constructor]
  auto config_dir = "OGRE_CONFIG_DIR=" MY_OGRE_CONFIG_DIR;
  putenv(config_dir);
  auto res = getenv("OGRE_CONFIG_DIR");
#endif
  try {
    TestApp app("Hello World");
    app.run();
  } catch (const std::exception& e) {
    std::cerr << "Error occurred during execution: " << e.what() << '\n';
    return 1;
  }

  return 0;
}

//! [starter]