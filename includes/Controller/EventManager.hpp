//
// Created by nicolas on 01/06/17.
//

#ifndef BOMBERMAN_EVENTMANAGER_HPP
#define BOMBERMAN_EVENTMANAGER_HPP

class EventManager;

#include <OgreFrameListener.h>
#include <OgreException.h>
#include <OIS/OIS.h>
#include <Ogre.h>
#include <CEGUI/RenderingWindow.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include "Common/Manager/GameManager.hpp"
#include "MapManager.hpp"

class EventManager
	: public Ogre::FrameListener, public Ogre::WindowEventListener,
	  public OIS::JoyStickListener
{
 private:
  Ogre::RenderWindow 		*mWindow;
  OIS::InputManager		*mInputManager;
  OIS::Keyboard 		*mKeyboard;
  OIS::JoyStickListener 	*mJoystick;
  OIS::Mouse 			*mMouse;
  Ogre::Camera 			*mCamera;
  CEGUI::OgreRenderer		*mRenderer;

  float 			mMovementspeed;

  MapManager			*_map;
  GameManager 			*game;

 public:


  EventManager(GameManager *, MapManager *, Ogre::RenderWindow *, Ogre::Camera *);

  ~EventManager();

  void windowClosed(Ogre::RenderWindow *windows);
  void windowResized(Ogre::RenderWindow *wnd);

  bool frameStarted(const Ogre::FrameEvent &evt);
  bool frameEnded(const Ogre::FrameEvent &evt);
  bool frameRenderingQueued(const Ogre::FrameEvent &evt);

  bool axisMoved(const OIS::JoyStickEvent &e, int axis);
  bool sliderMoved(const OIS::JoyStickEvent &e, int sliderID);
  bool buttonPressed(const OIS::JoyStickEvent &e, int button);
  bool buttonReleased(const OIS::JoyStickEvent &e, int button);
  bool vector3Moved(const OIS::JoyStickEvent &arg, int index);
  bool povMoved(const OIS::JoyStickEvent &arg, int index);

  void createSceneMenu();

  bool quit(const CEGUI::EventArgs &e);
};

#endif //BOMBERMAN_EVENTMANAGER_HPP
