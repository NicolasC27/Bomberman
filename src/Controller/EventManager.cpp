//
// Created by nicolas on 01/06/17.
//

#include "EventManager.hpp"


EventManager::EventManager()
{

}

EventManager::~EventManager()
{
  mInputManager->destroyInputObject(mKeyboard);
  mInputManager->destroyInputObject(mMouse);
  OIS::InputManager::destroyInputSystem(mInputManager);
}

void EventManager::initialize(Ogre::SceneNode *node, Ogre::RenderWindow *mWindow,
			      Ogre::Camera *camera)
{
  size_t windowHnd;
  std::stringstream windowHndStr;
  OIS::ParamList pl;

  windowHnd = 0;
  mNode = node;
  mCamera = camera;
  mMovementspeed = 5.0f;

  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
  mWindow->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;

  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
  mInputManager = OIS::InputManager::createInputSystem(pl);
  mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true ));
  mMouse = static_cast<OIS::Mouse *>(mInputManager->createInputObject(OIS::OISMouse, true));
//  if (mInputManager->getNumberOfDevices(OIS::OISJoyStick) > 0)
//    {
//      mJoystick = static_cast<OIS::JoyStick*>( mInputManager->createInputObject( OIS::OISJoyStick, true ) );
//      mJoystick = static_cast<OIS::JoyStick*>( mInputManager->createInputObject( OIS::OISJoyStick, true ) );
//      mJoystick = static_cast<OIS::JoyStick*>( mInputManager->createInputObject( OIS::OISJoyStick, true ) );
//      mJoystick->setEventCallback(this);
//    }
}

bool EventManager::capture(const Ogre::FrameEvent &evt)
{
  Ogre::Vector3 translate(0,0,0);

  mKeyboard->capture();
  mMouse->capture();
  mJoystick->capture();

  if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
      return false;
    }

  if(mKeyboard->isKeyDown(OIS::KC_W))
    {
      translate += Ogre::Vector3(0,0,-10);
    }

  if(mKeyboard->isKeyDown(OIS::KC_S))
    {
      translate += Ogre::Vector3(0,0,10);
    }

  if(mKeyboard->isKeyDown(OIS::KC_A))
    {
      translate += Ogre::Vector3(-10,0,0);
    }

  if(mKeyboard->isKeyDown(OIS::KC_D))
    {
      translate += Ogre::Vector3(10,0,0);
    }

  float rotY = mMouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
  float rotX = mMouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;

  mCamera->yaw(Ogre::Radian(rotX));
  mCamera->pitch(Ogre::Radian(rotY));

  mCamera->moveRelative(translate * evt.timeSinceLastFrame * mMovementspeed);

  return true;
}


bool EventManager::axisMoved(const OIS::JoyStickEvent &e, int axis)
{
  if( e.state.mAxes[axis].abs > 2500 || e.state.mAxes[axis].abs < -2500 )
    std::cout << std::endl << e.device->vendor() << ". Axis # " << axis << " Value: " << e.state.mAxes[axis].abs;
}

bool EventManager::buttonPressed(const OIS::JoyStickEvent &e, int button)
{
  std::cout << "buttonPressed : " <<  button << std::endl;
  return true;
}

bool EventManager::buttonReleased(const OIS::JoyStickEvent &e, int button)
{
  std::cout << "buttonReleased : " <<  button << std::endl;

  return true;
}

bool EventManager::sliderMoved(const OIS::JoyStickEvent &e, int sliderID)
{
  std::cout << "sliderMoved : " <<  sliderID << std::endl;

  return true;
}

bool EventManager::vector3Moved(const OIS::JoyStickEvent &arg, int index)
{
  return true;
}

bool EventManager::povMoved(const OIS::JoyStickEvent &arg, int index)
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