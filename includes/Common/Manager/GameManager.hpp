//
// Created by nicolas on 04/06/17.
//

#ifndef BOMBERMAN_GAMEMANAGER_HPP
#define BOMBERMAN_GAMEMANAGER_HPP

#include <Ogre.h>
#include "Controller/EventManager.hpp"
#include "Common/Manager/CameraManager.hpp"
#include "NodeManager.hpp"

#define NAME_GAME	"Bomberman"

class GameManager
{
 private:
  Controller::EventManager	*Listener;

  Ogre::Root 		*_Root;
  Ogre::SceneManager 	*_SceneManager;
  Ogre::RenderWindow 	*_Window;
  Ogre::Light 		*_Light;
  CameraManager		*Camera;
  NodeManager 		*_nodes;

 public:
  GameManager();
  virtual ~GameManager();

  void 			initializeResources();
  void 			createRenderWindow();
  void 			setupScene();
  void 			setupLight();
  void 			run();

  Ogre::Root 		*getRoot() const;
  Ogre::SceneManager 	*getSceneManager() const;
  Ogre::RenderWindow 	*getWindow() const;
  NodeManager 		*getNodes() const;
};

#endif //BOMBERMAN_GAMEMANAGER_HPP
