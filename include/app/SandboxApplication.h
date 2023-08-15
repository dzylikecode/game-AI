#pragma once
#include <memory>
#include <string>

#include "app/BaseApplication.h"
#include "object/Sandbox.h"

class SandboxApplication : public BaseApplication {
 public:
  SandboxApplication(const String& appName) : BaseApplication(appName) {
    m_timer.reset();
    lastRenderTime = m_timer.getMicroseconds();
    lastUpdateTime = m_timer.getMicroseconds();
  }
  virtual ~SandboxApplication() {}

  void setup() override;
  void shutdown() override;

  bool frameStarted(const FrameEvent& evt) override;
  bool frameEnded(const FrameEvent& evt) override;

  void createSandbox(const String& scriptName);
  void addResourceLocation(const String& location) {
    ResourceGroupManager::getSingleton().addResourceLocation(location,
                                                             "FileSystem");
  }

 private:
  Timer m_timer;
  uint64_t lastRenderTime;
  uint64_t lastUpdateTime;  // sandbox update time

  shared_ptr<Sandbox> m_sandbox;

  int m_sandboxId;
  std::unique_ptr<DebugDrawerAI> m_debugDrawer;

 private:
  int generateSandboxId() { return m_sandboxId++; }
};
