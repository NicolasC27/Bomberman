// Created by nicolas on 01/06/17.

#include "Objects/Player.hpp"
#include "Controller/EventManager.hpp"
#include <Overlay/OgreFontManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreTextAreaOverlayElement.h>
#include <iostream>

EventManager::EventManager(GameManager *gameManager, MapManager *map, Ogre::RenderWindow *Window, Ogre::Camera *camera) : _map(map), game(gameManager)
{
  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

  OIS::ParamList pl;
  std::stringstream windowHndStr;
  size_t windowHnd = 0;

  mWindow = Window;
  mCamera = camera;
  mMovementspeed = 5.0f;
  mWindow->getCustomAttribute("WINDOW", &windowHnd);

  windowHndStr << windowHnd;

  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
  mInputManager = OIS::InputManager::createInputSystem(pl);

  mKeyboard = static_cast<OIS::Keyboard *>(mInputManager->createInputObject(
	  OIS::OISKeyboard, true));
  mMouse = static_cast<OIS::Mouse *>(mInputManager->createInputObject(
	  OIS::OISMouse, true));


  //todo debug Joystick
  //  if (mInputManager->getNumberOfDevices(OIS::OISJoyStick) > 0)
//    {
//      mJoystick = static_cast<OIS::JoyStick*>( mInputManager->createInputObject( OIS::OISJoyStick, true ) );
//      mJoystick = static_cast<OIS::JoyStick*>( mInputManager->createInputObject( OIS::OISJoyStick, true ) );
//      mJoystick = static_cast<OIS::JoyStick*>( mInputManager->createInputObject( OIS::OISJoyStick, true ) );
//      mJoystick->setEventCallback(this);
//    }
  windowResized(mWindow);
}

EventManager::~EventManager()
{

  mInputManager->destroyInputObject(mKeyboard);
  mInputManager->destroyInputObject(mMouse);

  OIS::InputManager::destroyInputSystem(mInputManager);
  Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
  windowClosed(mWindow);
}

void 			EventManager::windowClosed(Ogre::RenderWindow *windows)
{
  if (windows == mWindow)
    {
      if (mInputManager)
	{
	  mInputManager->destroyInputObject(mMouse);
	  mInputManager->destroyInputObject(mKeyboard);

	  OIS::InputManager::destroyInputSystem(mInputManager);
	  mInputManager = 0;
	}
    }
}

void 			EventManager::windowResized(Ogre::RenderWindow *windows)
{
  unsigned int width, height, depth;
  int left, top;

  windows->getMetrics(width, height, depth, left, top);
  const OIS::MouseState &ms = mMouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

bool 			EventManager::frameStarted(const Ogre::FrameEvent &evt)
{
  return true;
}


bool 			EventManager::frameEnded(const Ogre::FrameEvent &evt)
{
  return true;
}


bool 			EventManager::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
  Ogre::Vector3 	translate(0, 0, 0);
  Ogre::Real 		pause = 0;

  if (mWindow->isClosed())
    return false;
  mKeyboard->capture();
  mMouse->capture();

      Player *player;
      std::vector<AGameObject *> Character = _map->getCharacter();

      for (std::vector<AGameObject *>::const_iterator characterit = Character.begin();
	   characterit != Character.end(); ++characterit)
	{
	  player = dynamic_cast<Player *>(*characterit);

	  for (std::map<OIS::KeyCode, Player::ActionKeyCode>::const_iterator keyit = player->getKeyCodeType().begin();
	       keyit != player->getKeyCodeType().end(); ++keyit)
	    {
	      if (mKeyboard->isKeyDown(keyit->first))
		if (game->getState() == GameManager::GAME)
		    player->action(keyit->second, evt);
	    }
	  if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
	    return false;
	  else
	    if (mKeyboard->isKeyDown(OIS::KC_R))
	      game->setState(GameManager::RESTART);
	    else
	      if (mKeyboard->isKeyDown(OIS::KC_P))
		{
		  pause -= evt.timeSinceLastEvent;
		  if (pause <= 0)
		    {
		      if (game->getState() == GameManager::GAME)
			{
			  game->setState(GameManager::PAUSE);
			  pause = 0.5;
			}
		      else
			{
			  game->setState(GameManager::GAME);
			  pause = 0.5;
			}
		    }
		}
	  else if (mKeyboard->isKeyDown(OIS::KC_J))
	      game->reset();
    }
  if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    return false;
  if (mKeyboard->isKeyDown(OIS::KC_I))
    translate += Ogre::Vector3(0, 0, -10);
  if (mKeyboard->isKeyDown(OIS::KC_K))
    translate += Ogre::Vector3(0, 0, 10);
  if (mKeyboard->isKeyDown(OIS::KC_A))
    translate += Ogre::Vector3(-10, 0, 0);
  if (mKeyboard->isKeyDown(OIS::KC_L))
    translate += Ogre::Vector3(10, 0, 0);
  float rotX = mMouse->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
  float rotY = mMouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
  for (std::vector<AGameObject *>::const_iterator characterit = Character.begin();
	  characterit != Character.end(); ++characterit)
  {
	  player = dynamic_cast<Player *>(*characterit);
	  player->tick();
	  std::cout << "toto" << std::endl;
  }
  std::cout << std::endl;
  mCamera->yaw(Ogre::Radian(rotX));
  mCamera->pitch(Ogre::Radian(rotY));
  mCamera->moveRelative(translate * evt.timeSinceLastFrame * 400);


//  float rotX = mMouse->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
//  float rotY = mMouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
//  mCamera->yaw(Ogre::Radian(rotX));
//  mCamera->pitch(Ogre::Radian(rotY));
//
//  mCamera->moveRelative(translate * evt.timeSinceLastFrame * mMovementspeed * 5);

  game->update(evt.timeSinceLastFrame);
  return true;
}

bool 			EventManager::axisMoved(const OIS::JoyStickEvent &e, int axis)
{
  if( e.state.mAxes[axis].abs > 2500 || e.state.mAxes[axis].abs < -2500 )
    std::cout << std::endl << e.device->vendor() << ". Axis # " << axis << " Value: " << e.state.mAxes[axis].abs;
  return true;
}

bool 			EventManager::buttonPressed(const OIS::JoyStickEvent &e, int button)
{
  std::cout << "buttonPressed : " <<  button << std::endl;
  return true;
}

bool 			EventManager::buttonReleased(const OIS::JoyStickEvent &e, int button)
{
  std::cout << "buttonReleased : " <<  button << std::endl;

  return true;
}

bool 			EventManager::sliderMoved(const OIS::JoyStickEvent &e, int sliderID)
{
  std::cout << "sliderMoved : " <<  sliderID << std::endl;

  return true;
}

bool 			EventManager::vector3Moved(const OIS::JoyStickEvent &arg, int index)
{
  return true;
}

bool 			EventManager::povMoved(const OIS::JoyStickEvent &arg, int index)
{
  Ogre::Vector3 translate(0,0,0);

  if (arg.state.mPOV[index].direction == arg.state.mPOV->North)
    {
      translate += Ogre::Vector3(0, 0, -10);
    } else
    if (arg.state.mPOV[index].direction == arg.state.mPOV->South)
      {
	translate += Ogre::Vector3(0, 0, 10);
      } else
      if (arg.state.mPOV[index].direction == arg.state.mPOV->East)
	{
	  translate += Ogre::Vector3(10, 0, 0);
	} else
	if (arg.state.mPOV[index].direction == arg.state.mPOV->West)
	  {
	    translate += Ogre::Vector3(-10, 0, 0);
	  }

//  mCamera->moveRelative(translate * 0.5);

  return true;
}