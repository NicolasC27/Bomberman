//
// Created by nicolas on 04/06/17.
//

#include <OgreSceneManager.h>
#include <Objects/Player.hpp>
#include "Objects/Wall.hpp"
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

  _Root = new Ogre::Root(mPluginsCfg);

  Ogre::ConfigFile cf;
  cf.load(mResourcesCfg);

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
  if(_Root->restoreConfig()  || _Root->showConfigDialog())
     createRenderWindow();
  initializeResources();
  setupScene();
  this->_hudManager = new HudManager(this);
}

GameManager::~GameManager()
{

}

void 			GameManager::setWallFalling()
{
  wallFalling.x = MapManager::boxWidth;
  wallFalling.z = _boundary;
  wallFalling.timer = 60;
  wallFalling.turn = 0;
}

void 			GameManager::run()
{
  _timer = GAME_TIME;
  _map = new MapManager("media/map/map2", getSceneManager());
  _map->generateObjects(false);
  setupLight();
  _boundary = (_map->getSize() - 2) * MapManager::boxWidth;
  setWallFalling();
  Camera = new CameraManager(getSceneManager(), getWindow(), _map->getSize());

  Listener = new EventManager(this, _map, getWindow(), Camera->getCamera());
  _Root->addFrameListener(Listener);
  _Root->startRendering();
}

void			GameManager::checkVictory()
{
  MapManager::Character	charac = _map->getCharacter();

  if (charac.size() <= 1)
    {
      if (charac.size() == 1)
	static_cast<Player *>(charac[0])->setPoints(static_cast<Player *>(charac[0])->getPoint() + 100);
      _map->getEngine()->play2D(_map->getWinner());
      reset();
    }
}

void 			GameManager::update(Ogre::Real dt)
{
  if (_state == RESTART)
    reset();
  else
    if (_state == GAME)
      {
	if (_timer <= 0)
	  _timer = 0;
	else
	  _timer -= dt;
	_map->deleteWaitObject();
	this->WallFalling(dt);
	_map->update(dt);
	checkVictory();
	this->_hudManager->showHud(this->_map);
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
      if (_timer + dt > 0)
	_map->getEngine()->play2D(_map->getFall());
      if (wallFalling.timer <= 0 && _map->getWallFrom(Ogre::Vector2(wallFalling.x, wallFalling.z)) == NULL)
	{
	  AGameObject *wall;
	  if ((wall = _map->getObjectFrom(Ogre::Vector2(wallFalling.x, wallFalling.z))) == NULL ||
	      wall->getState() != AGameObject::UNBREAKABLE_BLOCK)
	    {
	      wall = new Wall(_map, AGameObject::UNBREAKABLE_WALL);
	      dynamic_cast<Wall *>(wall)->setPositionY(800);
	      _map->addWall(Ogre::Vector2(wallFalling.x, wallFalling.z), wall);
	      wallFalling.timer = 60;
	    }
	  nextFoundingPositionWallFalling();
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

  _Light->setPosition(Ogre::Vector3((_map->getSize() * 100) / 2,
				    (_map->getSize() * 100) + (_map->getSize() * 100) / 10,
				    -(_map->getSize() * 100) / 5));
  _Light->setDiffuseColour(Ogre::ColourValue::White);
  _Light->setSpecularColour(Ogre::ColourValue::White);

  _Light->setAttenuation((_map->getSize() * 100) * 2,1,0.000,0);
}

void 			GameManager::reset()
{
  _map->reset();
  _timer = 120;
  setWallFalling();
  setState(GAME);
}

Ogre::RenderWindow	*GameManager::getWindow() const
{
  return _Window;
}

GameManager::State 	GameManager::getState() const
{
  return _state;
}

void 			GameManager::setState(GameManager::State state)
{
  _state = state;
}
