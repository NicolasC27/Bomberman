//
// Created by nicolas on 04/06/17.
//

#include <OgreSceneManager.h>
#include "Objects/Wall.hpp"
#include "Common/Manager/ConfigManager.hpp"
#include "Common/Manager/GameManager.hpp"

GameManager::GameManager()
{
  Ogre::String mResourcesCfg;
  Ogre::String mPluginsCfg;
#ifdef _DEBUG
  mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
  mResourcesCfg = "resources.cfg";
  mPluginsCfg = "plugins.cfg";
#endif

  // construct Ogre::Root
  _Root = new Ogre::Root(mPluginsCfg);

//-------------------------------------------------------------------------------------
  // setup resources
  // Load resource paths from config file
  Ogre::ConfigFile cf;
  cf.load(mResourcesCfg);

  // Go through all sections & settings in the file
  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

  Ogre::String secName, typeName, archName;
  while (seci.hasMoreElements())
    {
      secName = seci.peekNextKey();
      Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
      Ogre::ConfigFile::SettingsMultiMap::iterator i;
      for (i = settings->begin(); i != settings->end(); ++i)
	{
	  typeName = i->first;
	  archName = i->second;
	  Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		  archName, typeName, secName);
	}
    }
  if(_Root->restoreConfig())
    {
      _Window = _Root->initialise(true, NAME_GAME);
    }
  initializeResources();
  setupScene();
  setupLight();
}

GameManager::~GameManager()
{

}

void 			GameManager::run()
{
  MapManager *Map = new MapManager("media/map/map1", getSceneManager(), getNodes());
  Map->generateObjects();
  wallFalling.x = MapManager::boxWidth;
  wallFalling.z = (Map->getSize() * MapManager::boxWidth) - 200;


  Camera = new CameraManager(getSceneManager(), getWindow(), Map->getSize());

  Listener = new EventManager(this, Map, getWindow(), Camera->getCamera());
  getRoot()->addFrameListener(Listener);
  getRoot()->startRendering();
}

void 			GameManager::update(MapManager *map, Ogre::Real dt)
{
  _timer -= dt;

  this->WallFalling(map, dt);

  map->update(dt);
//  std::cout << _timer << std::endl;
}

void 			GameManager::nextFoundingPositionWallFalling(MapManager *map)
{
  if (wallFalling.x == CUBE_WIDTH + wallFalling.turn && (wallFalling.z > CUBE_WIDTH + wallFalling.turn &&
							 wallFalling.z <=
							 (map->getSize() * MapManager::boxWidth) - 200))
    {
      wallFalling.z -= CUBE_WIDTH;
    } else
    if (wallFalling.z == CUBE_WIDTH + wallFalling.turn && (wallFalling.x >= CUBE_WIDTH
							   && wallFalling.x <
							      (map->getSize() * MapManager::boxWidth) - 200 - wallFalling.turn))
      {
	wallFalling.x += CUBE_WIDTH;

      } else
      if (wallFalling.x == (map->getSize() * MapManager::boxWidth) - 200 - wallFalling.turn &&
	  (wallFalling.z >= CUBE_WIDTH + wallFalling.turn &&
	   wallFalling.z < (map->getSize() * MapManager::boxWidth) - 200 - wallFalling.turn))
	{
	  wallFalling.z += CUBE_WIDTH;

	} else
	if (wallFalling.z == 900 - wallFalling.turn && (wallFalling.x > 200 &&
							wallFalling.x <=
							(map->getSize() * MapManager::boxWidth) - 200 - wallFalling.turn))
	  {
	    wallFalling.x -= CUBE_WIDTH;
	    if (wallFalling.x - wallFalling.turn == MapManager::boxWidth + 100)
	      wallFalling.turn += 100;
	  }
}

void 			GameManager::WallFalling(MapManager *map, Ogre::Real dt)
{
  static int 		i = 0;

  if (_timer <= 0 && i == 0 &&  map->getIsdestructible() > 1)
    {
      if (wallFalling.timer <= 0)
	{
	  AGameObject *wall;
	  wall = new Wall(map, AGameObject::UNBREAKABLE);
	  dynamic_cast<Wall *>(wall)->setPositionY(800);
	  map->addObjects(Ogre::Vector2(wallFalling.x, wallFalling.z), wall);
	  map->setIsdestructible(map->getIsdestructible() - 1);
	  while (map->getIsdestructible() > 1 &&
		 map->getObject(Ogre::Vector2(wallFalling.x, wallFalling.z)))
	    nextFoundingPositionWallFalling(map);
	  wallFalling.timer = 60;
	}
      wallFalling.timer -= dt;
    }
}

void 			GameManager::createRenderWindow()
{
  _Window = _Root->initialise(true, NAME_GAME);
}

void 			GameManager::initializeResources()
{
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(1);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void 			GameManager::setupScene()
{
  _SceneManager = _Root->createSceneManager(Ogre::ST_GENERIC, "Bomberman Game");
  _SceneManager->setAmbientLight(Ogre::ColourValue(0.4f, 0.4f, 0.4f));
}

Ogre::SceneManager*	GameManager::getSceneManager() const
{
  return _SceneManager;
}

void 			GameManager::setupLight()
{
  Ogre::Light *_Light = _SceneManager->createLight("Light1");
  _Light->setType(Ogre::Light::LT_POINT);
  _Light->setPosition(Ogre::Vector3(1100, 500, 1100));
  _Light->setDiffuseColour(Ogre::ColourValue::White);
  _Light->setSpecularColour(Ogre::ColourValue::White);

  _Light->setAttenuation(2000,1,0,0);

  _Light = _SceneManager->createLight("Light Red");
  _Light->setType(Ogre::Light::LT_POINT);
  _Light->setPosition(Ogre::Vector3(250, 500, 1000));
  _Light->setDiffuseColour(Ogre::ColourValue::Red);
  _Light->setSpecularColour(Ogre::ColourValue::Red);

  _Light->setAttenuation(1000,1,0.007,0);

}

Ogre::Root*		GameManager::getRoot() const
{
  return _Root;
}

Ogre::RenderWindow*	GameManager::getWindow() const
{
  return _Window;
}

NodeManager*		GameManager::getNodes() const
{
  return _nodes;
}