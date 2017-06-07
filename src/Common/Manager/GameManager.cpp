//
// Created by nicolas on 04/06/17.
//

#include <OgreSceneManager.h>
#include <tiff.h>
#include "Common/Manager/ConfigManager.hpp"
#include "Common/Manager/GameManager.hpp"
#include "Map.hpp"

using namespace Controller;

GameManager::GameManager()
{
//  ConfigManager configManager(_Root);
//
//  _Root = configManager.getRoot();
  _Root = new Ogre::Root;

  // Configures the application
  if (!_Root->restoreConfig())
    _Root->showConfigDialog();
  _Root->saveConfig();
  Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media/materials", "FileSystem");
  Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media/materials/scripts", "FileSystem");
  Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media/materials/textures", "FileSystem");
  Ogre::ResourceGroupManager::getSingleton().addResourceLocation("media/models", "FileSystem");

  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  createRenderWindow();
  initializeResources();
  setupScene();
  setupLight();
}

GameManager::~GameManager()
{

}

void 			GameManager::run()
{
  Map 			map("media/map/map1", getSceneManager(), getNodes());

  map.generateObjects();
  Camera = new CameraManager(getSceneManager(), getWindow(), map.getSize());

  Listener = new EventManager(getWindow(), Camera->getCamera());
  getRoot()->addFrameListener(Listener);
  getRoot()->startRendering();
}

void 			GameManager::createRenderWindow()
{
  _Window = _Root->initialise(true, NAME_GAME);
}

void 			GameManager::initializeResources()
{
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(1);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void 			GameManager::setupScene()
{
  _SceneManager = _Root->createSceneManager(Ogre::ST_GENERIC, "Bomberman Game");
  _SceneManager->setAmbientLight(Ogre::ColourValue(0.4f, 0.4f, 0.4f));
}

Ogre::SceneManager*	GameManager::getSceneManager() const
{
  return _SceneManager;
}

void 			GameManager::setupLight()
{
  Ogre::Light *_Light = _SceneManager->createLight("Light1");
  _Light->setType(Ogre::Light::LT_POINT);
  _Light->setPosition(Ogre::Vector3(250, 500, 250));
  _Light->setDiffuseColour(Ogre::ColourValue::White);
  _Light->setSpecularColour(Ogre::ColourValue::White);

  _Light->setAttenuation(1000,1,0.007,0);

  _Light = _SceneManager->createLight("Light Red");
  _Light->setType(Ogre::Light::LT_POINT);
  _Light->setPosition(Ogre::Vector3(250, 500, 1000));
  _Light->setDiffuseColour(Ogre::ColourValue::Red);
  _Light->setSpecularColour(Ogre::ColourValue::Red);

  _Light->setAttenuation(1000,1,0.007,0);

}

Ogre::Root*		GameManager::getRoot() const
{
  return _Root;
}

Ogre::RenderWindow*	GameManager::getWindow() const
{
  return _Window;
}

NodeManager*	GameManager::getNodes() const
{
  return _nodes;
}
