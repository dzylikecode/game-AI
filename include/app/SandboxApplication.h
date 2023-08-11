#pragma once
#include <string>

#include "app/BaseApplication.h"
#include "resources/LuaFileManager.h"
#include "sandbox/Sandbox.h"
#include "utils/Timer.h"

class SandboxApplication : public BaseApplication {
 public:
  SandboxApplication(const String& applicationTitle, const int width = 800,
                     const int height = 600);
  virtual ~SandboxApplication();

  virtual void init() override;
  /**
   * @brief
   *
   * @return true if the application should continue running, false otherwise.
   */
  virtual bool update() override;
  virtual void shutdown() override;

  void createSandbox(const String& scriptName);

 private:
  Timer m_timer;
  double m_lastUpdateTime;

  Sandbox* m_sandbox;

 private:
  void handleInput();
  void updateSandBox();
};

// #include "utils/Timer.h"
// #include "utils/type.h"

// class LuaFileManager;
// class Sandbox;

// class SandboxApplication : public BaseApplication {
//  public:
//   SandboxApplication(const String& applicationTitle);

//   virtual ~SandboxApplication();

//   void AddResourceLocation(const String& location);

//   virtual void Cleanup();

//   virtual void CreateSandbox(const String& sandboxLuaScript);

//   virtual void Draw();

//   int GenerateSandboxId();

//   virtual Sandbox* GetSandbox();

//   virtual void HandleKeyPress(const KeyCode keycode, unsigned int key);

//   virtual void HandleKeyRelease(const KeyCode keycode, unsigned int key);

//   virtual void HandleMouseMove(const int width, const int height);

//   virtual void HandleMousePress(const int width, const int height,
//                                 const OIS::MouseButtonID button);

//   virtual void HandleMouseRelease(const int width, const int height,
//                                   const OIS::MouseButtonID button);

//   virtual void Initialize();

//   virtual void Update();

//  private:
//  private:
//   double m_lastUpdateTimeInMicro;
//   double m_lastUpdateCallTime;

//   LuaFileManager* m_luaFileManager;

//   Sandbox* m_sandbox;
//   Timer m_timer;

//   int m_lastSandboxId;

//   SandboxApplication(const SandboxApplication&);
//   SandboxApplication& operator=(const SandboxApplication&);
// };
