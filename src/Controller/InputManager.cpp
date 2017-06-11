//
// Created by nicolas on 31/05/17.
//

#include "InputManager.hpp"

class EventManager : public FrameListener {
 private:
  OIS::InputManager* mInputManager;
  OIS::Keyboard* mKeyboard;
  OIS::Mouse* mMouse;
  Ogre::SceneNode* mNode;
  Ogre::Camera *mCamera;
  float mMovementspeed;

 public:
  EventManager(Ogre::SceneNode*,RenderWindow*, Ogre::Camera*);
  ~EventManager();
  bool frameStarted (const FrameEvent &evt);
  bool frameEnded (const FrameEvent &evt);
  bool frameRenderingQueued (const FrameEvent &evt);
};

//
EventManager::EventManager(Ogre::SceneNode *node, RenderWindow *mWindow, Ogre::Camera *camera)
{
  //
  mNode = node;
  mCamera = camera;
  mMovementspeed = 5.0f;

  //
  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

  //
  size_t windowHnd = 0;
  mWindow->getCustomAttribute("WINDOW", &windowHnd);

  //
  std::stringstream windowHndStr;
  windowHndStr << windowHnd;

  //
  OIS::ParamList pl;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
  mInputManager = OIS::InputManager::createInputSystem(pl);

  //
  mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true ));
  mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));i
}

//
EventManager::~EventManager()
{
  //
  mInputManager->destroyInputObject(mKeyboard);
  mInputManager->destroyInputObject(mMouse);
  OIS::InputManager::destroyInputSystem(mInputManager);
}

//
bool EventManager::frameStarted(const FrameEvent &evt) {
  //std::cout << "Frame Started" << std::endl;

  //
  Ogre::Vector3 translate(0,0,0);

  //
  mKeyboard->capture();
  mMouse->capture();

  //
  if(mKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
      return false;
    }

  //
  if(mKeyboard->isKeyDown(OIS::KC_W))
    {
      translate += Ogre::Vector3(0,0,-10);
    }

  //
  if(mKeyboard->isKeyDown(OIS::KC_S))
    {
      translate += Ogre::Vector3(0,0,10);
    }

  //
  if(mKeyboard->isKeyDown(OIS::KC_A))
    {
      translate += Ogre::Vector3(-10,0,0);
    }

  //
  if(mKeyboard->isKeyDown(OIS::KC_D))
    {
      translate += Ogre::Vector3(10,0,0);
    }

  //
  float rotX = mMouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
  float rotY = mMouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;
  mCamera->yaw(Ogre::Radian(rotX));
  mCamera->pitch(Ogre::Radian(rotY));

  //
  mCamera->moveRelative(translate * evt.timeSinceLastFrame * mMovementspeed);

  return true;
}

//
bool EventManager::frameEnded(const FrameEvent &evt) {
  //std::cout << "Frame Ended" << std::endl;
  return true;
}

//
bool EventManager::frameRenderingQueued(const FrameEvent &evt) {
  //std::cout << "Frame Queued" << std::endl;
  return true;
}