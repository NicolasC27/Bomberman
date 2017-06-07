//
// Created by nicolas on 06/06/17.
//

#ifndef BOMBERMAN_CAMERAMANAGER_HPP
#define BOMBERMAN_CAMERAMANAGER_HPP


#include <OgreVector3.h>
#include <Ogre.h>

class CameraManager
{
 public:
  CameraManager(Ogre::SceneManager *SceneManager, Ogre::RenderWindow *Window, int sizemap);
  CameraManager();
  virtual ~CameraManager();

  Ogre::Camera		*getCamera() const;

 private:
  Ogre::Camera		*_Camera;
  Ogre::Viewport	*_vp;
  int 			_sizemap;

  void 			setVp(Ogre::RenderWindow *Window);
  void 			setCamera(Ogre::SceneManager *SceneManager);
};


#endif //BOMBERMAN_CAMERAMANAGER_HPP
