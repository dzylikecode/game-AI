#pragma once
#include <Ogre.h>
#include <OgreApplicationContext.h>
#include <OgreInput.h>

#include <memory>

#include "debug/DebugDrawer.h"

using namespace Ogre;
using namespace OgreBites;

class BaseApplication : public ApplicationContext, public InputListener {
 public:
  BaseApplication(const String& appName = "")
      : ApplicationContext(appName),
        m_camera(nullptr),
        m_sceneManager(nullptr) {}
  virtual ~BaseApplication(){};

  auto getCamera() const { return m_camera; }
  auto getSceneManager() const { return m_sceneManager; }

  void setup() override;

  bool keyPressed(const KeyboardEvent& evt) override;

  void run();

 private:
  Camera* m_camera;
  SceneManager* m_sceneManager;
};