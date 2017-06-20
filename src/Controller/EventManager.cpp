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
  std::map<OIS::KeyCode, Player::ActionKeyCode>::const_iterator keyit;
  std::map<OIS::KeyCode, Player::ActionKeyCode>::const_iterator keyend;
  Ogre::Vector3 translate(0, 0, 0);
  static OIS::KeyCode lastKey = OIS::KC_ESCAPE;
  Player *player;
  std::vector<AGameObject *> Character = _map->getCharacter();

  mKeyboard->capture();
  mMouse->capture();

  if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    return false;
  else
    if (lastKey != OIS::KC_R && mKeyboard->isKeyDown(OIS::KC_R))
      {
	game->setState(GameManager::RESTART);
	lastKey = OIS::KC_R;
      } else
      if (lastKey != OIS::KC_P && mKeyboard->isKeyDown(OIS::KC_P))
	{
	  game->setState(GameManager::PAUSE);
	  _map->getEngine()->play2D(_map->getPause());
	  lastKey = OIS::KC_P;
	} else
	if (mKeyboard->isKeyDown(OIS::KC_O))
	  {
	    _map->getEngine()->play2D(_map->getConfirm());
	    game->setState(GameManager::GAME);
	    lastKey = OIS::KC_O;
	  }
  if (game->getState() == GameManager::GAME)
    {
      lastKey = OIS::KC_ESCAPE;
      for (std::vector<AGameObject *>::const_iterator characterit = Character.begin();
	   characterit != Character.end();)
	{
	  if ((player = dynamic_cast<Player *>(*characterit)) == NULL)
	    continue;
	  ++characterit;
	  keyit = player->getKeyCodeType().begin();
	  keyend = player->getKeyCodeType().end();
	  for (; player != NULL && keyit != keyend; ++keyit)
	    {
	      if ((mKeyboard->isKeyDown(keyit->first)))
		player->action(keyit->second, evt);
	    }
	}
      if (mKeyboard->isKeyDown(OIS::KC_G))
	translate += Ogre::Vector3(0, 0, -10);
      if (mKeyboard->isKeyDown(OIS::KC_B))
	translate += Ogre::Vector3(0, 0, 10);
      if (mKeyboard->isKeyDown(OIS::KC_V))
	translate += Ogre::Vector3(-10, 0, 0);
      if (mKeyboard->isKeyDown(OIS::KC_N))
	translate += Ogre::Vector3(10, 0, 0);
      for (std::vector<AGameObject *>::const_iterator characterit = Character.begin(); characterit != Character.end(); ++characterit)
	{
	  player = dynamic_cast<Player *>(*characterit);
	  player->tick();
	}

      mCamera->moveRelative(translate * evt.timeSinceLastFrame * 400);

    }

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
  return true;
}

bool 			EventManager::buttonReleased(const OIS::JoyStickEvent &e, int button)
{
  return true;
}

bool 			EventManager::sliderMoved(const OIS::JoyStickEvent &e, int sliderID)
{
  return true;
}

bool 			EventManager::vector3Moved(const OIS::JoyStickEvent &arg, int index)
{
  return true;
}

bool 			EventManager::povMoved(const OIS::JoyStickEvent &arg, int index)
{
  Ogre::Vector3 translate(0, 0, 0);

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

  return true;
}