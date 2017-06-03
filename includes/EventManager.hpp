//
// Created by nicolas on 01/06/17.
//

#ifndef BOMBERMAN_EVENTMANAGER_HPP
#define BOMBERMAN_EVENTMANAGER_HPP

#include <OgreFrameListener.h>
#include "InputManager.hpp"
#include <OgreException.h>
#include <OIS/OIS.h>
#include <Ogre.h>

class EventManager : public Ogre::FrameListener,  public Ogre::WindowEventListener
{
 private:
  Ogre::RenderWindow 	*mWindow;
  OIS::InputManager 	*mInputManager;
  OIS::Keyboard 	*mKeyboard;
  OIS::Mouse 		*mMouse;
  Ogre::Camera 		*mCamera;
  float mMovementspeed;

 public:
  EventManager(Ogre::RenderWindow *, Ogre::Camera *);
  ~EventManager();

  void windowClosed(Ogre::RenderWindow *windows);
  void windowResized(Ogre::RenderWindow *wnd);

  bool frameStarted(const Ogre::FrameEvent &evt);
  bool frameEnded(const Ogre::FrameEvent &evt);
  bool frameRenderingQueued(const Ogre::FrameEvent &evt);
};


#endif //BOMBERMAN_EVENTMANAGER_HPP
