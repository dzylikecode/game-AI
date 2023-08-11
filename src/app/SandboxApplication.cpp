#include "app/SandboxApplication.h"

#include <raylib.h>
#include <spdlog/spdlog.h>

#include "debug/DebugDrawer.h"

SandboxApplication::SandboxApplication(const String& applicationTitle,
                                       const int width, const int height)
    : BaseApplication(applicationTitle, width, height),
      m_timer(),
      m_sandbox(nullptr) {
  m_timer.reset();
  m_lastUpdateTime = m_timer.getSeconds();
}

SandboxApplication::~SandboxApplication() {}

void SandboxApplication::init() { m_lastUpdateTime = m_timer.getSeconds(); }

bool SandboxApplication::update() {
  BeginDrawing();
  ClearBackground(RAYWHITE);
  EndDrawing();

  handleInput();
  updateSandBox();

  if (WindowShouldClose()) return false;

  return true;
}

void SandboxApplication::handleInput() {}

void SandboxApplication::updateSandBox() {
  constexpr double updatePerSecond = 1.0 / 30;
  const auto currentTime = m_timer.getSeconds();
  const auto deltaTime = currentTime - m_lastUpdateTime;

  if (!m_sandbox) return;

  m_sandbox->setProfileTime(Sandbox::RENDER_TIME, 1.0 / GetFPS());

  if (deltaTime >= updatePerSecond) {
    m_sandbox->setProfileTime(Sandbox::TOTAL_SIMULATION_TIME, deltaTime);
    DebugDrawer::getInstance().clear();
    const auto startUpdateTime = currentTime;
    // Fixed time step regardless of actual time that has passed.
    m_sandbox->update(updatePerSecond);
    const auto endUpdateTime = m_timer.getSeconds();
    m_sandbox->setProfileTime(Sandbox::SIMULATION_TIME,
                              endUpdateTime - startUpdateTime);
    DebugDrawer::getInstance().build();
    m_lastUpdateTime = currentTime;
  }
}

void SandboxApplication::shutdown() {}

void SandboxApplication::createSandbox(const String& scriptName) {
  SPDLOG_INFO("Sandbox: Creating sandbox \"{}\"", scriptName);

  if (m_sandbox) {
    delete m_sandbox;
  }

  m_sandbox = new Sandbox(scriptName);
}

// #include <raylib.h>
// #include <spdlog/spdlog.h>

// #include "demo_framework/include/DebugDrawer.h"
// #include "demo_framework/include/LuaFileManager.h"
// #include "demo_framework/include/LuaFilePtr.h"
// #include "demo_framework/include/Sandbox.h"

// SandboxApplication::SandboxApplication(const String& applicationTitle)
//     : BaseApplication(applicationTitle),
//       m_lastSandboxId(-1),
//       m_sandbox(nullptr),
//       m_luaFileManager(nullptr) {
//   m_timer.reset();

//   m_lastUpdateTimeInMicro = m_timer.getSeconds();
//   m_lastUpdateCallTime = m_timer.getSeconds();
// }

// SandboxApplication::~SandboxApplication() {
//   delete m_luaFileManager;

//   if (m_sandbox) {
//     delete m_sandbox;
//   }
// }

// void SandboxApplication::AddResourceLocation(const String& location) {
//   Ogre::ResourceGroupManager::getSingleton().addResourceLocation(location,
//                                                                  "FileSystem");
// }

// void SandboxApplication::Cleanup() {
//   if (m_sandbox) {
//     m_sandbox->Cleanup();
//   }
// }

// void SandboxApplication::CreateSandbox(const String& sandboxLuaScript) {
//   SPDLOG_INFO("Sandbox: Creating sandbox \"{}\"", sandboxLuaScript);

//   LuaFilePtr script = m_luaFileManager->load(
//       sandboxLuaScript,
//       Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

//   const auto sandboxNode =
//       GetSceneManager()->getRootSceneNode()->createChildSceneNode();

//   if (m_sandbox) {
//     delete m_sandbox;
//   }

//   m_sandbox = new Sandbox(GenerateSandboxId(), sandboxNode, GetCamera());

//   m_sandbox->LoadScript(script->GetData(), script->GetDataLength(),
//                         script->getName().c_str());

//   m_sandbox->Initialize();

//   SPDLOG_INFO("Sandbox: Finished creating sandbox \"{}\"", sandboxLuaScript);
// }

// void SandboxApplication::Draw() {
//   const auto currentTime = m_timer.getSeconds();

//   m_sandbox->SetProfileTime(Sandbox::RENDER_TIME,
//                             currentTime - m_lastUpdateCallTime);

//   m_lastUpdateCallTime = currentTime;
// }

// int SandboxApplication::GenerateSandboxId() { return ++lastSandboxId_; }

// Sandbox* SandboxApplication::GetSandbox() { return m_sandbox; }

// void SandboxApplication::HandleKeyPress(const KeyCode keycode,
//                                         unsigned int key) {
//   if (m_sandbox) {
//     m_sandbox->HandleKeyPress(keycode, key);
//   }
// }

// void SandboxApplication::HandleKeyRelease(const KeyCode keycode,
//                                           unsigned int key) {
//   if (m_sandbox) {
//     m_sandbox->HandleKeyRelease(keycode, key);
//   }
// }

// void SandboxApplication::HandleMouseMove(const int width, const int height) {
//   if (m_sandbox) {
//     m_sandbox->HandleMouseMove(width, height);
//   }
// }

// void SandboxApplication::HandleMousePress(const int width, const int height,
//                                           const OIS::MouseButtonID button) {
//   if (m_sandbox) {
//     m_sandbox->HandleMousePress(width, height, button);
//   }
// }

// void SandboxApplication::HandleMouseRelease(const int width, const int
// height,
//                                             const OIS::MouseButtonID button)
//                                             {
//   if (m_sandbox) {
//     m_sandbox->HandleMouseRelease(width, height, button);
//   }
// }

// void SandboxApplication::Initialize() {
//   m_luaFileManager = new LuaFileManager();

//   const Ogre::ColourValue ambient(0.0f, 0.0f, 0.0f);

//   GetRenderWindow()->getViewport(0)->setBackgroundColour(ambient);
//   GetSceneManager()->setAmbientLight(ambient);
//   GetSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

//   GetCamera()->setFarClipDistance(1000.0f);
//   GetCamera()->setNearClipDistance(0.1f);
//   GetCamera()->setAutoAspectRatio(true);

//   GetRenderWindow()->setDeactivateOnFocusChange(false);

//   Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(4);

//   m_lastUpdateTimeInMicro = m_timer.getSeconds();

//   AddResourceLocation("../../../src/demo_framework/script");

//   Gorilla::Silverback* mSilverback = new Gorilla::Silverback();
//   mSilverback->loadAtlas("fonts/dejavu/dejavu");
//   Gorilla::Screen* mScreen = mSilverback->createScreen(
//       GetCamera()->getViewport(), "fonts/dejavu/dejavu");
//   Gorilla::Layer* mLayer = mScreen->createLayer(0);

// #ifdef NDEBUG
// #define BUILD_TYPE "RELEASE"
// #else
// #define BUILD_TYPE "DEBUG"
// #endif

//   Gorilla::MarkupText* const text = mLayer->createMarkupText(
//       91, mScreen->getWidth(), mScreen->getHeight(),
//       "Learning Game AI Programming with Lua v1.0 " BUILD_TYPE
//       " " __TIMESTAMP__);

//   text->left(mScreen->getWidth() - text->maxTextWidth() - 4);
//   text->top(mScreen->getHeight() -
//             mScreen->getAtlas()->getGlyphData(9)->mLineHeight - 4);

//   mLayer->setVisible(true);
//   // mLayer->setVisible(false);
// }

// void SandboxApplication::Update() {
//   // The sandbox simulation will update 30 times per second.
//   static const long long updatePerSecondInMicros = 1000000 / 30;

//   const long long currentTimeInMicro = m_timer.getSeconds();

//   const long long timeDeltaInMicros =
//       currentTimeInMicro - m_lastUpdateTimeInMicro;

//   if (m_sandbox && timeDeltaInMicros >= updatePerSecondInMicros) {
//     m_sandbox->SetProfileTime(Sandbox::TOTAL_SIMULATION_TIME,
//                               currentTimeInMicro - m_lastUpdateTimeInMicro);

//     // Flush out the previous debug graphics.
//     DebugDrawer::getSingleton().clear();

//     // Fixed time step regardless of actual time that has passed.
//     m_sandbox->Update(static_cast<int>(updatePerSecondInMicros / 1000));

//     m_lastUpdateTimeInMicro = currentTimeInMicro;

//     DebugDrawer::getSingleton().build();

//     m_sandbox->SetProfileTime(Sandbox::SIMULATION_TIME,
//                               m_timer.getSeconds() - currentTimeInMicro);
//   }
// }
