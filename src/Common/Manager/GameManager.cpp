//
// Created by nicolas on 04/06/17.
//

#include <OgreSceneManager.h>
#include "Objects/Wall.hpp"
#include "Common/Manager/ConfigManager.hpp"
#include "Common/Manager/GameManager.hpp"

GameManager::GameManager() : _state(GAME)
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
  _Root = std::unique_ptr<Ogre::Root>(new Ogre::Root(mPluginsCfg));

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
  if((*_Root).restoreConfig()  || (*_Root).showConfigDialog())
    {
      _Window = (*_Root).initialise(true, NAME_GAME);
    }
  initializeResources();
  setupScene();
  setupLight();
}

GameManager::~GameManager()
{
  //delete _map;
  //delete _Root;
}

void 			GameManager::run()
{
  _map = new MapManager("media/map/map1", getSceneManager(), getNodes());
  _map->generateObjects(false);
  _boundary = (_map->getSize() - 2) * MapManager::boxWidth;
  wallFalling.x = MapManager::boxWidth;
  wallFalling.z = _boundary;


  Camera = new CameraManager(getSceneManager(), getWindow(), _map->getSize());

  Listener = new EventManager(this, _map, getWindow(), Camera->getCamera());
  (*_Root).addFrameListener(Listener);
  (*_Root).startRendering();
}

void			GameManager::checkVictory()
{
  if (_map->getCharacter().size() <= 1)
    {

    }
}

void 			GameManager::update(Ogre::Real dt)
{
  if (_state != PAUSE)
    {
      _timer -= dt;

      this->WallFalling(dt);

      _map->update(dt);
      checkVictory();
    }
}

void 			GameManager::nextFoundingPositionWallFalling()
{
  if ((wallFalling.x == CUBE_WIDTH + wallFalling.turn) &&
      (wallFalling.z > CUBE_WIDTH + wallFalling.turn) &&
      (wallFalling.z <= _boundary))
    wallFalling.z -= CUBE_WIDTH;
  else if ((wallFalling.z == CUBE_WIDTH + wallFalling.turn) &&
	   (wallFalling.x >= CUBE_WIDTH) &&
	   (wallFalling.x < _boundary - wallFalling.turn))
    wallFalling.x += CUBE_WIDTH;
  else if ((wallFalling.x == _boundary - wallFalling.turn) &&
	   (wallFalling.z >= CUBE_WIDTH + wallFalling.turn) &&
	   (wallFalling.z < _boundary - wallFalling.turn))
    wallFalling.z += CUBE_WIDTH;
  else if ((wallFalling.z == _boundary - wallFalling.turn) &&
	   (wallFalling.x > 2 * MapManager::boxWidth) &&
	   (wallFalling.x <= _boundary - wallFalling.turn))
  {
    wallFalling.x -= CUBE_WIDTH;
    if (wallFalling.x - wallFalling.turn == MapManager::boxWidth * 2)
      wallFalling.turn += MapManager::boxWidth;
  }
}

void 			GameManager::WallFalling(Ogre::Real dt)
{
  if (_timer <= 0)
    {
      if (wallFalling.timer <= 0)
	{
	  AGameObject *wall;
	  wall = new Wall(_map, AGameObject::UNBREAKABLE_WALL);
	  dynamic_cast<Wall *>(wall)->setPositionY(800);
	  _map->addObjects(Ogre::Vector2(wallFalling.x, wallFalling.z), wall);
	  //map->setIsdestructible(map->getIsdestructible() - 1);
	  while (/*map->getIsdestructible() > 1 &&*/
		 _map->getObject(Ogre::Vector2(wallFalling.x, wallFalling.z)))
	    nextFoundingPositionWallFalling();
	  wallFalling.timer = 60;
	}
      wallFalling.timer -= dt;
    }
}

void 			GameManager::createRenderWindow()
{
  _Window = (*_Root).initialise(true, NAME_GAME);
}

void 			GameManager::initializeResources()
{
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(1);
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void 			GameManager::setupScene()
{
  _SceneManager = (*_Root).createSceneManager(Ogre::ST_GENERIC, "Bomberman Game");
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

  _Light->setPosition(Ogre::Vector3(550, 1192, -200));
  _Light->setDiffuseColour(Ogre::ColourValue::White);
  _Light->setSpecularColour(Ogre::ColourValue::White);

  _Light->setAttenuation(2000,1,0.000,0);

//  _Light = _SceneManager->createLight("Light Red");
//  _Light->setType(Ogre::Light::LT_POINT);
//  _Light->setPosition(Ogre::Vector3(250, 550, 1000));
//  _Light->setDiffuseColour(Ogre::ColourValue::Red);
//  _Light->setSpecularColour(Ogre::ColourValue::Red);
//
//  _Light->setAttenuation(1000,1,0,0);

}

Ogre::RenderWindow*	GameManager::getWindow() const
{
  return _Window;
}

NodeManager*		GameManager::getNodes() const
{
  return _nodes;
}

void 			GameManager::reset()
{
  _map->reset();
  wallFalling.x = 0;
  wallFalling.z = 0;
  wallFalling.turn = 0;
  wallFalling.timer = 60;
}

GameManager::State 	GameManager::getState() const
{
  return _state;
}

void 			GameManager::setState(GameManager::State state)
{
  _state = state;
}
