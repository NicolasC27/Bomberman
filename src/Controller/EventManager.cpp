// Created by nicolas on 01/06/17.

#include "Controller/EventManager.hpp"

EventManager::EventManager(MapManager *map, Ogre::RenderWindow *Window, Ogre::Camera *camera) : _map(map)
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

  if (mWindow->isClosed())
    return false;
  mKeyboard->capture();
  mMouse->capture();

  float mMoveScale;
  Ogre::Degree mRotScale;
  Ogre::Real mTimeUntilNextToggle;
  Ogre::Real mMoveSpeed;
  Ogre::Degree mRotateSpeed;

  if (mTimeUntilNextToggle >= 0)
    mTimeUntilNextToggle -= evt.timeSinceLastFrame;

  mMoveScale = mMoveSpeed * evt.timeSinceLastFrame;
  mRotScale = mRotateSpeed * evt.timeSinceLastFrame;

  Ogre::Radian mRotX, mRotY;
  mRotX = 0;
  mRotY = 0;

  Ogre::Vector3 mTranslateVector;
  mTranslateVector = Ogre::Vector3::ZERO;


  if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    return false;

  if (mKeyboard->isKeyDown(OIS::KC_W))
    _map->move(Ogre::Vector3(0, 0, 1), evt);

  if (mKeyboard->isKeyDown(OIS::KC_S))
    _map->move(Ogre::Vector3(0, 0, -1), evt);

  if (mKeyboard->isKeyDown(OIS::KC_A))
    _map->move(Ogre::Vector3(1, 0, 0), evt);

  if (mKeyboard->isKeyDown(OIS::KC_D))
    _map->move(Ogre::Vector3(-1, 0, 0), evt);



//
//  if (mKeyboard->isKeyDown(OIS::KC_ESCAPE))
//    return false;
//
//  if (mKeyboard->isKeyDown(OIS::KC_W))
//    translate += Ogre::Vector3(0, 0, -10);
//
//  if (mKeyboard->isKeyDown(OIS::KC_S))
//    translate += Ogre::Vector3(0, 0, 10);
//
//  if (mKeyboard->isKeyDown(OIS::KC_A))
//    translate += Ogre::Vector3(-10, 0, 0);
//
//  if (mKeyboard->isKeyDown(OIS::KC_D))
//    translate += Ogre::Vector3(10, 0, 0);
//



  float rotX = mMouse->getMouseState().X.rel * evt.timeSinceLastFrame * -1;
  float rotY = mMouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
  mCamera->yaw(Ogre::Radian(rotX));
  mCamera->pitch(Ogre::Radian(rotY));

  mCamera->moveRelative(translate * evt.timeSinceLastFrame * mMovementspeed * 5);
  return true;
}

bool 			EventManager::axisMoved(const OIS::JoyStickEvent &e, int axis)
{
  if( e.state.mAxes[axis].abs > 2500 || e.state.mAxes[axis].abs < -2500 )
    std::cout << std::endl << e.device->vendor() << ". Axis # " << axis << " Value: " << e.state.mAxes[axis].abs;
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

  mCamera->moveRelative(translate * 0.5);

  return true;
}