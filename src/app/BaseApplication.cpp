#include "app/BaseApplication.h"

#include <OgreRTShaderSystem.h>

void BaseApplication::setup() {
  ApplicationContext::setup();
  addInputListener(this);

  auto root = getRoot();
  m_sceneManager = root->createSceneManager();

  auto shadergen = RTShader::ShaderGenerator::getSingletonPtr();
  shadergen->addSceneManager(m_sceneManager);

  auto camNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
  m_camera = m_sceneManager->createCamera("PlayerCamera");
  camNode->setPosition(0, 1.0f, 0);
  camNode->lookAt(Vector3(0, 0, -1.0f), Node::TransformSpace::TS_WORLD);
  m_camera->setAutoAspectRatio(true);
  m_camera->setNearClipDistance(0.001f);
  camNode->attachObject(m_camera);

  auto vp = getRenderWindow()->addViewport(m_camera);
  vp->setBackgroundColour(ColourValue(0, 0, 0));

  m_camera->setAspectRatio(Real(vp->getActualWidth()) /
                           Real(vp->getActualHeight()));
}

bool BaseApplication::keyPressed(const KeyboardEvent& evt) {
  if (evt.keysym.sym == SDLK_ESCAPE) {
    getRoot()->queueEndRendering();
  } else if (evt.keysym.sym == 'r') {
    String newVal;
    PolygonMode pm;

    switch (m_camera->getPolygonMode()) {
      case Ogre::PM_SOLID:
        newVal = "Wireframe";
        pm = Ogre::PM_WIREFRAME;
        break;
      case Ogre::PM_WIREFRAME:
        newVal = "Points";
        pm = Ogre::PM_POINTS;
        break;
      default:
        newVal = "Solid";
        pm = Ogre::PM_SOLID;
    }

    m_camera->setPolygonMode(pm);
  } else if (evt.keysym.sym == SDLK_F12) {
    TextureManager::getSingleton().reloadAll();
  } else if (evt.keysym.sym == SDLK_PRINTSCREEN) {
    getRenderWindow()->writeContentsToTimestampedFile("ogre-screenshot",
                                                      ".png");
  }
  return true;
}
void BaseApplication::run() {
  initApp();
  getRoot()->startRendering();
  closeApp();
}