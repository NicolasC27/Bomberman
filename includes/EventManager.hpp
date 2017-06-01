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

class EventManager : public Ogre::FrameListener, public OIS::JoyStickListener
{
 public:
  EventManager();
  ~EventManager();

  bool capture(const Ogre::FrameEvent &evt);
  void initialize(Ogre::SceneNode *, Ogre::RenderWindow *, Ogre::Camera *);

  bool axisMoved(const OIS::JoyStickEvent &e, int axis);
  bool sliderMoved(const OIS::JoyStickEvent &e, int sliderID);
  bool buttonPressed(const OIS::JoyStickEvent &e, int button);
  bool buttonReleased(const OIS::JoyStickEvent &e, int button);
  bool vector3Moved(const OIS::JoyStickEvent &arg, int index);
  bool povMoved(const OIS::JoyStickEvent &arg, int index);

 private:
  OIS::InputManager 	*mInputManager;
  OIS::Keyboard 	*mKeyboard;
  OIS::Mouse 		*mMouse;
  OIS::JoyStick 	*mJoystick;
  Ogre::SceneNode 	*mNode;
  Ogre::Camera 		*mCamera;

  float 		mMovementspeed;

};

#endif //BOMBERMAN_EVENTMANAGER_HPP
