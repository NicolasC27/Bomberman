// Created by nicolas on 01/06/17.


#include "EventManager.hpp"

EventManager::EventManager(Ogre::RenderWindow *Window, Ogre::Camera *camera)
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
  Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
}

EventManager::~EventManager()
{

  mInputManager->destroyInputObject(mKeyboard);
  mInputManager->destroyInputObject(mMouse);

  OIS::InputManager::destroyInputSystem(mInputManager);
  Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
  windowClosed(mWindow);
}

void EventManager::windowClosed(Ogre::RenderWindow *windows)
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

void EventManager::windowResized(Ogre::RenderWindow *windows)
{
  unsigned int width, height, depth;
  int left, top;

  windows->getMetrics(width, height, depth, left, top);
  const OIS::MouseState &ms = mMouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

bool EventManager::frameStarted(const Ogre::FrameEvent &evt)
{
  return true;
}


bool EventManager::frameEnded(const Ogre::FrameEvent &evt)
{
  return true;
}


bool EventManager::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
  Ogre::Vector3 translate(0, 0, 0);

  if (mWindow->isClosed())
    return false;
  mKeyboard->capture();
  mMouse->capture();


  if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    return false;

  if (mKeyboard->isKeyDown(OIS::KC_W))
    translate += Ogre::Vector3(0, 0, -10);

  if (mKeyboard->isKeyDown(OIS::KC_S))
    translate += Ogre::Vector3(0, 0, 10);

  if (mKeyboard->isKeyDown(OIS::KC_A))
    translate += Ogre::Vector3(-10, 0, 0);

  if (mKeyboard->isKeyDown(OIS::KC_D))
    translate += Ogre::Vector3(10, 0, 0);

  float rotX = mMouse->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
  float rotY = mMouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
  mCamera->yaw(Ogre::Radian(rotX));
  mCamera->pitch(Ogre::Radian(rotY));

  mCamera->moveRelative(translate * evt.timeSinceLastFrame * mMovementspeed);
  return true;
}