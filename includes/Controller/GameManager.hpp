//
// Created by nicolas on 04/06/17.
//

#ifndef BOMBERMAN_GAMEMANAGER_HPP
#define BOMBERMAN_GAMEMANAGER_HPP

#include <Ogre.h>
#include "NodeManager.hpp"

#define NAME_GAME	"Bomberman"

namespace Controller
{
  class GameManager
  {
   private:
    NodeManager			*_nodes;

   private:
    Ogre::Root 			*mRoot;
    Ogre::SceneManager		*mSceneManager;
    Ogre::RenderWindow		*mWindow;
    Ogre::Camera		*mCamera;
    Ogre::Light			*mLight;

   public:
    GameManager();
    virtual ~GameManager();

    void	initializeRoot();
    bool 	initializeConfigRender();
    void 	initializeResources();

    void 	createRenderWindow();

    void 	setupScene();
    void	setupCamera();
    void 	setupLight();

    Ogre::Root		*getMRoot() const;
    Ogre::Camera 	*getMCamera() const;
    Ogre::SceneManager 	*getMSceneManager() const;
    Ogre::RenderWindow 	*getMWindow() const;
    NodeManager 	*getNodes() const;

  };
}
#endif //BOMBERMAN_GAMEMANAGER_HPP
