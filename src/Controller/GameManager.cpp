//
// Created by nicolas on 04/06/17.
//

#include <OgreSceneManager.h>
#include "Controller/GameManager.hpp"

Controller::GameManager::GameManager()
{
  initializeRoot();
  initializeConfigRender();
  createRenderWindow();
  initializeResources();
  setupScene();
  setupCamera();
  setupLight();
}

Controller::GameManager::~GameManager()
{

}

void Controller::GameManager::initializeRoot()
{
  mRoot = new Ogre::Root("plugins.cfg", "ogre.cfg", "Ogre.log");
  Ogre::ConfigFile configFile;

  configFile.load("resources.cfg");
  Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator();
  Ogre::String secName, typeName, archName;
  while (seci.hasMoreElements())
    {
      secName = seci.peekNextKey();
      Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
      Ogre::ConfigFile::SettingsMultiMap::iterator i;
      for (i = settings->begin(); i != settings->end(); ++i)
	{
	  typeName = i->first;
	  archName = i->second;
	  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		  archName, typeName, secName);
	}
    }
}

bool Controller::GameManager::initializeConfigRender()
{
  Ogre::RenderSystem *rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");

  mRoot->setRenderSystem(rs);
  rs->setConfigOption("Full Screen", "No");
  rs->setConfigOption("Video Mode", "1280 x 800 @ 32-bit colour");
  rs->setConfigOption("VSync", "Yes");

  Ogre::ConfigOptionMap map = rs->getConfigOptions();
  for(Ogre::ConfigOptionMap::const_iterator it = map.begin(); it != map.end(); it++)
    {
      std::cout << it->first << std::endl;
      for(int i = 0; i < it->second.possibleValues.size(); i++)
	std::cout << "  " << it->second.possibleValues[i] << std::endl;
    }

  if(!(mRoot->restoreConfig() || mRoot->showConfigDialog())) {
      return false;
    }
}

void Controller::GameManager::createRenderWindow()
{
  mWindow = mRoot->initialise(true, NAME_GAME);
}

void Controller::GameManager::initializeResources()
{
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void Controller::GameManager::setupScene()
{
  mSceneManager = mRoot->createSceneManager(Ogre::ST_GENERIC, "Default SceneManager");
  mSceneManager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
}

void Controller::GameManager::setupCamera()
{
  mCamera = mSceneManager->createCamera("PlayerCam");
  mCamera->setPosition(Ogre::Vector3(0,0,100));
  mCamera->lookAt(Ogre::Vector3(0,0,0));
  mCamera->setNearClipDistance(5);


  Ogre::Viewport* vp = mWindow->addViewport(mCamera);
  vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
  vp->setOverlaysEnabled(true);
  mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

Ogre::SceneManager *Controller::GameManager::getMSceneManager() const
{
  return mSceneManager;
}

void Controller::GameManager::setupLight()
{
  mLight = mSceneManager->createLight("light1");
  mLight->setPosition(100, 300, 200);
//  light->setDiffuseColour(0.0, 0.0, 1.0);
//  light->setSpecularColour(0.0, 0.0, 1.0);
  mSceneManager->setAmbientLight(Ogre::ColourValue(0.0, 0.0, 0.0));

}

Ogre::Root *Controller::GameManager::getMRoot() const
{
  return mRoot;
}

Ogre::Camera *Controller::GameManager::getMCamera() const
{
  return mCamera;
}

Ogre::RenderWindow *Controller::GameManager::getMWindow() const
{
  return mWindow;
}

Controller::NodeManager *Controller::GameManager::getNodes() const
{
  return _nodes;
}
