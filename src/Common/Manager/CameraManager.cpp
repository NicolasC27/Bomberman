//
// Created by nicolas on 06/06/17.
//

#include <Common/Manager/CameraManager.hpp>
#include <MapManager.hpp>
#include <iostream>

CameraManager::CameraManager()
{

}

CameraManager::CameraManager(Ogre::SceneManager *SceneManager, Ogre::RenderWindow *Window, int sizemap) : _sizemap(sizemap)
{
  setCamera(SceneManager);
  setVp(Window);
}


CameraManager::~CameraManager()
{

}

void 			CameraManager::setCamera(Ogre::SceneManager *SceneManager)
{
  _Camera = SceneManager->createCamera("PlayerCam");
  std::cout << _sizemap << std::endl;
  _Camera->setPosition(Ogre::Vector3(550, 1192 , -200));
  _Camera->lookAt(Ogre::Vector3((_sizemap * 100) / 2, 0, (_sizemap * 100) / 2));
  _Camera->setNearClipDistance(5);
}

void 			CameraManager::setVp(Ogre::RenderWindow *Window)
{
  _vp = Window->addViewport(_Camera);
  _vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
  _vp->setOverlaysEnabled(true);
  _Camera->setAspectRatio(Ogre::Real(_vp->getActualWidth()) / Ogre::Real(_vp->getActualHeight()));
}

Ogre::Camera*		CameraManager::getCamera() const
{
  return _Camera;
}
