//
// Created by nicolas on 29/05/17.
//

#include <Ogre.h>
#include "MapManager.hpp"
#include "Objects/Wall.hpp"
#include "Objects/Explosion.hpp"
#include "Objects/Player.hpp"
#include "Objects/Bomb.hpp"


MapManager::MapManager(std::string const &filename, Ogre::SceneManager *SceneManager,
	 NodeManager *node) : _filename(filename), _SceneManager(SceneManager), _nodes(node), _isdestructible(0)
{
  std::ifstream infile(filename);

  if (!(infile.good()))
    throw Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND,
			  NOT_FOUND, FOLDER_MAP);
}

MapManager::~MapManager()
{

}


void 		MapManager::update(Ogre::Real dt)
{
  Objects::const_iterator iteratorObject;
  Character::const_iterator iteratorCharacter;
  AGameObject		  *tmp;

  for (iteratorObject = _objects.begin(); iteratorObject != _objects.end(); )
    {
      tmp = iteratorObject->first;
      ++iteratorObject;
      tmp->update(dt);
    }
  for (iteratorCharacter = _character.begin(); iteratorCharacter != _character.end(); iteratorCharacter++)
    {
      tmp = *iteratorCharacter;
      tmp->update(dt);
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
  plan->setMaterialName ("Objects/Ground/BumpyMetal");

  Ogre::SceneNode *node = _SceneManager->getRootSceneNode()->createChildSceneNode();
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
    addCharacter(Ogre::Vector2(100, 900));
    addCharacter(Ogre::Vector2(100, 100));
    //addBomb(Ogre::Vector2(900, 900));
    generatePlan();
    generateSpawn();
  }
}

void 		MapManager::generateSpawn()
{
  _spawns.push_back(Ogre::Vector2(boxWidth, boxWidth));
  _spawns.push_back(Ogre::Vector2(
	  (_size * boxWidth) - (boxWidth * 2),
	  (_size * boxWidth) - (boxWidth * 2)));_spawns.push_back(Ogre::Vector2(boxWidth,
				   (_size * boxWidth) -
				   (boxWidth * 2)));
  _spawns.push_back(Ogre::Vector2(
	  (_size * boxWidth) - (boxWidth * 2),
	  boxWidth));
}

void 		MapManager::addCharacter(const Ogre::Vector2 &vector)
{
  AGameObject	*player;

  player = new Player(this, AGameObject::CHARACTER);
  _character.push_back(player);
  player->setSceneManager(_SceneManager);
  player->createEntity();
  player->setPosition(vector.x, player->getPositionY(), vector.y);
  player->AttachObject();
}

void 		MapManager::addBomb(const Ogre::Vector2 &vector)
{
  (void)vector;
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

bool		MapManager::getObject(Ogre::Vector2 vector)
{
  Objects::const_iterator it = _objects.begin();

  while (it != _objects.end())
    {
      if (it->second == vector)
	return (true);
      it++;
    }
  return (false);
}

Ogre::Vector2		MapManager::getPosFrom(Ogre::Vector2 const &t) const
{
  Ogre::Vector2		tmp(t);
  float                 diffx = std::fmod(t.x, boxWidth);
  float                 diffy = std::fmod(t.y, boxWidth);

  tmp.x -= diffx;
  tmp.y -= diffy;
  if (diffx > halfboxWidth)
    tmp.x += boxWidth;
  if (diffy > halfboxWidth)
    tmp.y += boxWidth;
  return (tmp);
}

Ogre::Vector2		MapManager::getPosFrom(Ogre::Vector3 const &t) const
{
  Ogre::Vector2		tmp(t.x, t.z);
  float                 diffx = std::fmod(t.x, boxWidth);
  float                 diffy = std::fmod(t.z, boxWidth);

  tmp.x -= diffx;
  tmp.y -= diffy;
  if (diffx > halfboxWidth)
    tmp.x += boxWidth;
  if (diffy > halfboxWidth)
    tmp.y += boxWidth;
  return (tmp);
}

int 		MapManager::getIsdestructible() const
{
  return 	_isdestructible;
}

void 		MapManager::setIsdestructible(int isdestructible)
{
  _isdestructible = isdestructible;
}

const 		MapManager::Objects &MapManager::getObjects() const
{
  return _objects;
}

void 		MapManager::removeObject(AGameObject *object)
{
  if (object->getObj() != NULL)
    object->getObj()->detachFromParent();
  else
    object->getParticleSystem()->clear();
  _objects.erase(object);
  delete object;
}

void 		MapManager::removeCharacter(AGameObject *object)
{
  MapManager::Character::const_iterator it = _character.begin();

  for (; it != _character.end() && *it != object; ++it);
  if (it != _character.end())
    _character.erase(it);
  delete object;
}

void 		MapManager::reset()
{
  unsigned int i;
  MapManager::Objects::const_iterator iteratorObject;

  for (iteratorObject = _objects.begin(); iteratorObject != _objects.end(); )
    {
      delete iteratorObject->first;
      iteratorObject = _objects.erase(iteratorObject);
    }
  for (i = 0; i < _character.size(); ++i)
    {
      dynamic_cast<Player *>(_character[i])->reset();
      _character[i]->setPosition(_spawns[i].x, 0, _spawns[i].y);
    }
  if (i < 2)
    for (; i < 2; ++i)
      addCharacter(_spawns[i]);
  generateObjects(true);
}