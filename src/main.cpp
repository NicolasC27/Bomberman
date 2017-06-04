//
// Created by nicolas on 29/05/17.
//


#include "Map.hpp"
#include <Ogre.h>
#include "Controller/EventManager.hpp"
#include "Controller/GameManager.hpp"

using namespace Controller;
using namespace Ogre;

static int		test()
{
  GameManager		Game;

  Map map("media/map/map1", Game.getMSceneManager(), Game.getNodes());
  map.generateObjects();

  EventManager* myListener = new EventManager(Game.getMWindow(), Game.getMCamera());

  Game.getMRoot()->addFrameListener(myListener);

  Game.getMRoot()->startRendering();

  delete Game.getMRoot();
}

int 			main()
{
  try
    {
      test();
    }  catch (const Ogre::Exception &exception) {

      std::cerr << exception.what() << std::endl;
      return (EXIT_FAILURE);
    }
}
