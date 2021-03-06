//
// Created by nicolas on 29/05/17.
//

#include <Ogre.h>
#include <OgreSceneManager.h>
#include "MapManager.hpp"
#include "Objects/Wall.hpp"
#include "Objects/Explosion.hpp"
#include "Objects/Player.hpp"
#include "Objects/Bomb.hpp"


MapManager::MapManager(std::string const &filename, Ogre::SceneManager *SceneManager) : _filename(filename), _SceneManager(SceneManager), _isdestructible(0)
{
  _objects.clear();
  _waitDelete.clear();
  std::ifstream infile(filename);

  if (!(infile.good()))
    throw Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND,
			  NOT_FOUND, FOLDER_MAP);
  this->setSound();
}

MapManager::~MapManager()
{
  _spawns.clear();
  engine->removeSoundSource(general);
  engine->removeSoundSource(explosion);
  engine->removeSoundSource(pause);
  engine->removeSoundSource(winner);
  engine->removeSoundSource(confirm);
  engine->removeSoundSource(player_out);
  engine->removeSoundSource(getitem);
  engine->removeSoundSource(fall);
  engine->removeSoundSource(wallOnGround);
  engine->drop();
  delete engine;
}

void		MapManager::setSound()
{
  engine = irrklang::createIrrKlangDevice();

  general = engine->addSoundSourceFromFile("media/sound/Bomberman.wav");
  explosion = engine->addSoundSourceFromFile("media/sound/explosion.wav");
  explosion->setDefaultVolume(0.5f);
  pause = engine->addSoundSourceFromFile("media/sound/pause.wav");
  winner = engine->addSoundSourceFromFile("media/sound/Winner.wav");
  confirm = engine->addSoundSourceFromFile("media/sound/confirm.wav");
  player_out = engine->addSoundSourceFromFile("media/sound/PLAYER_OUT.wav");
  getitem = engine->addSoundSourceFromFile("media/sound/ITEM_GET.wav");
  fall = engine->addSoundSourceFromFile("media/sound/BC_END.wav");
  wallOnGround = engine->addSoundSourceFromFile("media/sound/BOS_JUMP.wav");
  wallOnGround->setDefaultVolume(0.5f);
  engine->setSoundVolume(0.07f);
  engine->play2D("media/sound/Bomberman.wav");
}

void 		MapManager::update(Ogre::Real dt)
{
  Objects::const_iterator iteratorObject;
  Character::const_iterator iteratorCharacter;
  Character::const_iterator iteratorWall;

  for (iteratorObject = _objects.begin(); iteratorObject != _objects.end(); ++iteratorObject)
    {
      iteratorObject->first->update(dt);
    }
  for (iteratorCharacter = _character.begin(); iteratorCharacter != _character.end(); ++iteratorCharacter)
    {
      (*iteratorCharacter)->update(dt);
    }
  for (iteratorWall = _walls.begin(); iteratorWall != _walls.end(); ++iteratorWall)
    {
      (*iteratorWall)->update(dt);
    }
}

void 		MapManager::addObjects(const Ogre::Vector2 &vector, AGameObject *object)
{
  _objects.insert(std::pair<AGameObject *, Ogre::Vector2>(object, vector));
  object->setSceneManager(_SceneManager);
  object->createEntity();
  object->setPosition(vector.x, object->getPositionY(), vector.y);
  object->AttachObject();
}

void 		MapManager::addWall(const Ogre::Vector2 &vector, AGameObject *object)
{
  _walls.push_back(object);
  object->setSceneManager(_SceneManager);
  object->createEntity();
  object->setPosition(vector.x, object->getPositionY(), vector.y);
  object->AttachObject();
}

void		MapManager::generatePlan()
{
  Ogre::Plane 		plane(Ogre::Vector3::UNIT_Y, 0);
  Ogre::Entity		*plan;

  Ogre::MeshManager::getSingleton().createPlane(
	  "ground",
	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  plane,
	  _size * 100, _size * 100, 20, 20,
	  true,
	  1, 5, 5,
	  Ogre::Vector3::UNIT_Z);

  plan = _SceneManager->createEntity("ground");
  plan->setMaterialName ("Objects/Ground/ice");

  Ogre::SceneNode *node = _SceneManager->getRootSceneNode()->createChildSceneNode();
  node->setPosition((_size * 100) / 2 - 50, -50, (_size * 100) / 2 - 55);
  node->attachObject(plan);

  Ogre::Plane 		plane_outside(Ogre::Vector3::UNIT_Y, -2);

  Ogre::MeshManager::getSingleton().createPlane(
	  "ground_outside",
	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  plane_outside,
	  _size * 1000, _size * 1000, 20, 20,
	  true,
	  1, 5, 5,
	  Ogre::Vector3::UNIT_Z);

  plan = _SceneManager->createEntity("ground_outside");
  plan->setMaterialName ("Objects/Ground/ice");

  node->setPosition((_size * 100) / 2 - 50, -50, (_size * 100) / 2 - 55);
  node->attachObject(plan);

}

void 		MapManager::generateObjects(bool res)
{
  std::ifstream infile(_filename);
  std::string 	line;
  std::string	digit;
  int 		count;

  std::getline(infile, line);
  setSize(std::stoi(line));
  if (_size > 40)
    throw Ogre::Exception(Ogre::Exception::ERR_INVALID_STATE,
			  ERR_MAPSIZE, _filename);
  for (int x = 0; std::getline(infile, line); x++)
  {
      for(int z = 0, i = 0; line[i]; i++, z++)
	{
	  if ((line[i] - '0') == 1)
	      addObjects(Ogre::Vector2(boxWidth * z, boxWidth * x), new Wall(this, Wall::UNBREAKABLE_WALL));
	  else if ((line[i] - '0')  == 2)
	      addObjects(Ogre::Vector2(boxWidth * z, boxWidth * x), new Wall(this, Wall::UNBREAKABLE_BLOCK));
	    else if ((line[i] - '0')  == 3)
		addObjects(Ogre::Vector2(boxWidth * z, boxWidth * x), new Wall(this, Wall::BREAKABLE));
	      else
	      _isdestructible += 1;
	}
      count = x;
  }
  if (count != (_size - 1))
    throw Ogre::Exception(Ogre::Exception::ERR_INVALID_STATE,
			  ERR_NBLINEMAP, _filename);
  if (!res)
  {
    generateSpawn();
    addCharacter(_spawns[0], 1);
    addCharacter(_spawns[1], 2);
    generatePlan();
  }
}

void 		MapManager::generateSpawn()
{
  _spawns.push_back(Ogre::Vector2(boxWidth, boxWidth));
  _spawns.push_back(Ogre::Vector2(
	  (_size * boxWidth) - (boxWidth * 2),
	  (_size * boxWidth) - (boxWidth * 2)));
  _spawns.push_back(Ogre::Vector2(boxWidth,
	             		 (_size * boxWidth) -
				 (boxWidth * 2)));
  _spawns.push_back(Ogre::Vector2(
	  (_size * boxWidth) - (boxWidth * 2),
	  boxWidth));
}

void 		MapManager::addCharacter(const Ogre::Vector2 &vector, int id)
{
  AGameObject	*player;

  player = new Player(this, AGameObject::CHARACTER, id);
  _character.push_back(player);
  player->setSceneManager(_SceneManager);
  player->createEntity();
  player->setPosition(vector.x, player->getPositionY(), vector.y);
  player->AttachObject();
}

void 		MapManager::setSize(int size)
{
  _size = size;
}

int 		MapManager::getSize() const
{
  return _size;
}

const MapManager::Character 		&MapManager::getCharacter() const
{
  return _character;
}

AGameObject			*MapManager::getObjectFrom(Ogre::Vector2 const &pos) const
{
  Objects::const_iterator	it = _objects.begin();

  while (it != _objects.end())
    {
      if (it->second == pos)
	return (it->first);
      it++;
    }
  return (NULL);
}

AGameObject			*MapManager::getWallFrom(Ogre::Vector2 const &pos) const
{
  std::vector<AGameObject*>::const_iterator	it = _walls.begin();

  while (it != _walls.end())
    {
      if (getPosFrom((*it)->getNode()->getPosition()) == pos)
	return (*it);
      it++;
    }
  return (NULL);
}

MapManager::Character			MapManager::getCharacterFrom(Ogre::Vector2 const &pos) const
{
  MapManager::Character			in;
  MapManager::Character::const_iterator	it = _character.begin();

  while (it != _character.end())
    {
      if (getPosFrom((*it)->getNode()->getPosition()) == pos)
	in.push_back(*it);
      it++;
    }
  return (in);
}

AGameObject			*MapManager::getObjectFrom(Ogre::Vector3 const &pos) const
{
  Objects::const_iterator	it = _objects.begin();
  Ogre::Vector2			tmp(pos.x, pos.z);
  
  while (it != _objects.end())
    {
      if (it->second == tmp)
	return (it->first);
      it++;
    }
  return (NULL);
}

AGameObject			*MapManager::getObjectFrom(int id) const
{
  Objects::const_iterator	it = _objects.begin();

  while (it != _objects.end())
    {
      if (it->first->getId() == id)
	return (it->first);
      it++;
    }
  return (NULL);
}

Ogre::Vector2			MapManager::getPosFrom(Ogre::Vector2 const &t) const
{
  Ogre::Vector2			tmp(t);
  float                 	diffx = std::fmod(t.x, boxWidth);
  float                 	diffy = std::fmod(t.y, boxWidth);

  tmp.x -= diffx;
  tmp.y -= diffy;
  if (diffx > halfboxWidth)
    tmp.x += boxWidth;
  if (diffy > halfboxWidth)
    tmp.y += boxWidth;
  return (tmp);
}

Ogre::Vector2			MapManager::getPosFrom(Ogre::Vector3 const &t) const
{
  Ogre::Vector2			tmp(t.x, t.z);
  float                 	diffx = std::fmod(t.x, boxWidth);
  float                 	diffy = std::fmod(t.z, boxWidth);

  tmp.x -= diffx;
  tmp.y -= diffy;
  if (diffx > halfboxWidth)
    tmp.x += boxWidth;
  if (diffy > halfboxWidth)
    tmp.y += boxWidth;
  return (tmp);
}

void 		MapManager::removeObject(AGameObject *object)
{
  if (object->getObj() != NULL)
    object->getObj()->detachFromParent();

    _waitDelete[object->getId()] = object;
}

void 		MapManager::removeWall(AGameObject *object)
{
  MapManager::Character::const_iterator it;

  it = std::find(_walls.begin(), _walls.end(), object);
}

void 		MapManager::removeCharacter(AGameObject *object)
{
  MapManager::Character::const_iterator it;

  it = std::find(_character.begin(), _character.end(), object);
  _waitDelete[(*it)->getId()] = *it;
}

void 		MapManager::reset()
{
  unsigned int i;
  AGameObject	*tmp;
  int 		id = -1;

  for (MapManager::Objects::const_iterator  iteratorObject = _objects.begin(); iteratorObject != _objects.end(); )
    {
      tmp = iteratorObject->first;
      ++iteratorObject;
      removeObject(tmp);
    }
  for (MapManager::Character::const_iterator  it = _walls.begin(); it != _walls.end(); )
    {
      delete *it;
      ++it;
      removeWall(tmp);
    }
  _walls.clear();
  for (i = 0; i < _character.size(); ++i)
    {
      dynamic_cast<Player *>(_character[i])->reset();
      _character[i]->setPosition(_spawns[i].x, _character[i]->getPositionY(), _spawns[i].y);
      id = dynamic_cast<Player *>(_character[i])->getID();
    }
  if (i < 2)
    for (; i < 2; ++i)
      addCharacter(_spawns[i], (i == 0 || id == 2) ? 1 : 2);
  generateObjects(true);
}

irrklang::ISoundEngine 		*MapManager::getEngine() const
{
  return engine;
}

irrklang::ISoundSource 		*MapManager::getExplosion() const
{
  return explosion;
}

void 				MapManager::deleteWaitObject()
{
  Character::const_iterator	it;
  AGameObject * object;

  Delete::const_iterator iter;
  for( iter = _waitDelete.begin(); iter != _waitDelete.end(); iter++ ) {
       object = iter->second;
    if (_objects.find(object) != _objects.end())
      _objects.erase(getObjectFrom(iter->first));
    else if ((it = std::find(_walls.begin(), _walls.end(), object)) != _walls.end())
      _walls.erase(it);
    else if ((it = std::find(_character.begin(), _character.end(), object)) != _character.end())
      _character.erase(it);
    delete object;
  }
  _waitDelete.clear();
}

irrklang::ISoundSource		*MapManager::getWallOnGround() const
{
  return wallOnGround;
}

irrklang::ISoundSource		*MapManager::getFall() const
{
  return fall;
}

irrklang::ISoundSource		*MapManager::getGetitem() const
{
  return getitem;
}

irrklang::ISoundSource		*MapManager::getPlayer_out() const
{
  return player_out;
}

irrklang::ISoundSource		*MapManager::getConfirm() const
{
  return confirm;
}

irrklang::ISoundSource		*MapManager::getWinner() const
{
  return winner;
}

irrklang::ISoundSource		*MapManager::getPause() const
{
  return pause;
}
