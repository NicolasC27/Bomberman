//
// Created by nicolas on 04/06/17.
//

#ifndef BOMBERMAN_GAMEMANAGER_HPP
#define BOMBERMAN_GAMEMANAGER_HPP

class GameManager;
class HudManager;

#include <Ogre.h>
#include "Controller/EventManager.hpp"
#include "Common/Manager/CameraManager.hpp"
#include "MapManager.hpp"
#include "HudManager.hh"

#define NAME_GAME	"Bomberman"

class GameManager
{
 public:
  enum State
  {
    PAUSE,
    RESTART,
    GAME
  };

 private:
  EventManager		*Listener;

  Ogre::Root 		*_Root;
  Ogre::SceneManager 	*_SceneManager;
  Ogre::Light 		*_Light;
  CameraManager		*Camera;
  NodeManager 		*_nodes;
  MapManager		*_map;
  HudManager		*_hudManager;

  State 		_state;

 public:
  
  Ogre::RenderWindow 	*_Window;
  float 		_timer = 120;
  
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
  State 		getState() const;

  void 			WallFalling(Ogre::Real dt);

  void 			nextFoundingPositionWallFalling();

  void 			setState(State state);

  struct position {
    int		x = 0;
    int 	z = 0;
    int		turn = 0;
    int 	timer = 60;
    int 	count = 0;
  };

  position		wallFalling;
  int			_boundary;

  void 			checkVictory();
};

#endif //BOMBERMAN_GAMEMANAGER_HPP
