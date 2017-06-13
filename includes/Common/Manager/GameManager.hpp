//
// Created by nicolas on 04/06/17.
//

#ifndef BOMBERMAN_GAMEMANAGER_HPP
#define BOMBERMAN_GAMEMANAGER_HPP

class GameManager;

#include <Ogre.h>
#include "Controller/EventManager.hpp"
#include "Common/Manager/CameraManager.hpp"
#include "MapManager.hpp"

#define NAME_GAME	"Bomberman"

class GameManager
{
 private:
  EventManager			*Listener;

  Ogre::Root 		*_Root;
  Ogre::SceneManager 	*_SceneManager;
  Ogre::RenderWindow 	*_Window;
  Ogre::Light 		*_Light;
  CameraManager		*Camera;
  NodeManager 		*_nodes;

  float 		_timer = 120;

 public:
  GameManager();
  virtual ~GameManager();

  void 			initializeResources();

  void 			createRenderWindow();

  void 			setupScene();
  void 			setupLight();

  void 			run();

  void 			update(MapManager *map, Ogre::Real dt);

  Ogre::Root 		*getRoot() const;
  Ogre::SceneManager 	*getSceneManager() const;
  Ogre::RenderWindow 	*getWindow() const;
  NodeManager 		*getNodes() const;

  void 			WallFalling(MapManager *map, Ogre::Real dt);
};

#endif //BOMBERMAN_GAMEMANAGER_HPP
