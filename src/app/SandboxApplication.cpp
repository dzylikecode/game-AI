#include "app/SandboxApplication.h"

#include <memory>

#include "debug/DebugDrawer.h"
#include "resources/LuaFile.h"

void SandboxApplication::setup() {
  BaseApplication::setup();

  // m_debugDrawer = std::make_unique<DebugDrawerAI>(getSceneManager(), 0.5f);

  const Ogre::ColourValue ambient(0.0f, 0.0f, 0.0f);

  getRenderWindow()->getViewport(0)->setBackgroundColour(ambient);
  getSceneManager()->setAmbientLight(ambient);
  getSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

  getCamera()->setFarClipDistance(1000.0f);
  getCamera()->setNearClipDistance(0.1f);
  getCamera()->setAutoAspectRatio(true);

  getRenderWindow()->setDeactivateOnFocusChange(false);

  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(4);

  lastRenderTime = m_timer.getMilliseconds();

#ifdef PROJECT_SOURCE_DIR
  addResourceLocation(PROJECT_SOURCE_DIR "/scripts");
#else
#error "PROJECT_SOURCE_DIR is not defined"
#endif

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
}

void SandboxApplication::shutdown() {
  if (m_sandbox) {
    m_sandbox->shutdown();
    m_sandbox = nullptr;
  }
  BaseApplication::shutdown();
}

bool SandboxApplication::frameStarted(const FrameEvent& evt) {
  if (m_sandbox == nullptr) return BaseApplication::frameStarted(evt);

  const auto currentTime = m_timer.getMicroseconds();
  const auto deltaTime = currentTime - lastRenderTime;
  lastRenderTime = currentTime;

  m_sandbox->setProfileTime(Sandbox::RENDER_TIME, deltaTime);

  return BaseApplication::frameStarted(evt);
}

bool SandboxApplication::frameEnded(const FrameEvent& evt) {
  if (m_sandbox == nullptr) return BaseApplication::frameEnded(evt);

  static const auto updatePerSecond = 1000000 / 30;
  const auto currentTime = m_timer.getMicroseconds();
  const auto deltaTime = currentTime - lastUpdateTime;

  // The sandbox simulation will update 30 times per second.
  if (deltaTime >= updatePerSecond) {
    lastUpdateTime = currentTime;  // time to update the sandbox
    m_sandbox->setProfileTime(Sandbox::TOTAL_SIMULATION_TIME, deltaTime);

    // Flush out the previous debug graphics.
    // DebugDrawerAI::getSingleton().clear();

    // Fixed time step regardless of actual time that has passed.
    m_sandbox->update(updatePerSecond / 1000);

    // DebugDrawerAI::getSingleton().build();

    m_sandbox->setProfileTime(Sandbox::SIMULATION_TIME,
                              m_timer.getMicroseconds() - currentTime);
  }
  return BaseApplication::frameEnded(evt);
}

void SandboxApplication::createSandbox(const String& scriptName) {
  LogManager::getSingletonPtr()->logMessage(
      "Sandbox: Creating sandbox \"" + scriptName + "\"", Ogre::LML_NORMAL);
  auto script = LoadLuaFile(scriptName);
  auto sandboxNode =
      getSceneManager()->getRootSceneNode()->createChildSceneNode();
  m_sandbox =
      std::make_shared<Sandbox>(generateSandboxId(), sandboxNode, getCamera());
  m_sandbox->loadScript(script->data(), script->getSize(), scriptName.c_str());
  m_sandbox->setup();
  Ogre::LogManager::getSingletonPtr()->logMessage(
      "Sandbox: Finished creating sandbox \"" + scriptName + "\"",
      Ogre::LML_NORMAL);
}