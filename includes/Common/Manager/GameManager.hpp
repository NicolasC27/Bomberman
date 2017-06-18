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
  EventManager		*Listener;

  Ogre::Root 		*_Root;
  Ogre::SceneManager 	*_SceneManager;
  Ogre::RenderWindow 	*_Window;
  Ogre::Light 		*_Light;
  CameraManager		*Camera;
  NodeManager 		*_nodes;
  MapManager		*_map;
  float 		_timer = 10;

 public:
  GameManager();
  virtual ~GameManager();

  void 			initializeResources();

  void 			createRenderWindow();

  void 			setupScene();
  void 			setupLight();

  void 			run();

  void 			update(Ogre::Real dt);
  void 			reset();

  Ogre::Root 		*getRoot() const;
  Ogre::SceneManager 	*getSceneManager() const;
  Ogre::RenderWindow 	*getWindow() const;
  NodeManager 		*getNodes() const;

  void 			WallFalling(Ogre::Real dt);

  void 			nextFoundingPositionWallFalling();

  struct position {
    int		x = 0;
    int 	z = 0;
    int		turn = 0;
    int 	timer = 60;
    int 	count = 0;
  };

  position		wallFalling;
  int			_boundary;

  //bool checkAround();

//  bool checkAround();
};

#endif //BOMBERMAN_GAMEMANAGER_HPP
