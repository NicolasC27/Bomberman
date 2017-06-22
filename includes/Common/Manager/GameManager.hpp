//
// Created by nicolas on 04/06/17.
//

#ifndef BOMBERMAN_GAMEMANAGER_HPP
#define BOMBERMAN_GAMEMANAGER_HPP

class GameManager;
class HudManager;

#include <Ogre.h>
#include <irrKlang.h>
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
 static const int GAME_TIME = 120;
 private:
  EventManager		*Listener;

  Ogre::Root		*_Root;
  Ogre::SceneManager 	*_SceneManager;
  CameraManager		*Camera;
  NodeManager 		*_nodes;
  MapManager		*_map;
  HudManager		*_hudManager;

  State 		_state;

 public:
  
  Ogre::RenderWindow 	*_Window;
  float 		_timer;
  
  GameManager();
  virtual ~GameManager();

  void 			initializeResources();

  void 			createRenderWindow();

  void 			setupScene();
  void 			setupLight();

  void 			setWallFalling();
  void 			run();

  void 			update(Ogre::Real dt);
  void 			reset();

  Ogre::SceneManager 	*getSceneManager() const;
  Ogre::RenderWindow 	*getWindow() const;
  NodeManager 		*getNodes() const;
  State 		getState() const;

  void 			WallFalling(Ogre::Real dt);

  void 			nextFoundingPositionWallFalling();

  void 			setState(State state);

  struct position {
    int		x;
    int 	z;
    int		turn ;
    int 	timer;
  };

  position		wallFalling;
  int			_boundary;

  void 			checkVictory();
};

#endif //BOMBERMAN_GAMEMANAGER_HPP
