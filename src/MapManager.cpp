//
// Created by nicolas on 29/05/17.
//

#include <Ogre.h>
#include "Objects/Wall.hpp"
#include "Objects/Player.hpp"
#include "Objects/Bomb.hpp"
#include "MapManager.hpp"


MapManager::MapManager(std::string const &filename, Ogre::SceneManager *SceneManager,
	 NodeManager *node) : _filename(filename), _SceneManager(SceneManager), _nodes(node)
{
  std::ifstream infile(filename);

  if (!(infile.good()))
    throw Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND,
			  NOT_FOUND, FOLDER_MAP);
}

MapManager::~MapManager()
{

}

void 		MapManager::addObjects(const Ogre::Vector2 &vector, AGameObject *object)
{
  _objects.insert(std::pair<Ogre::Vector2, AGameObject *>(vector, object));
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

void 		MapManager::generateObjects()
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
	  if ((line[i] - '0') == AGameObject::WALL)
	    addObjects(Ogre::Vector2(MapManager::boxWidth * z, MapManager::boxWidth * x), new Wall(Wall::UNBREAKABLE));
	  else if ((line[i] - '0')  == AGameObject::BLOCK)
	      addObjects(Ogre::Vector2(MapManager::boxWidth * z, MapManager::boxWidth * x), new Wall(Wall::BREAKABLE));
	}
      count = x;
  }
  if (count != (_size - 1))
    throw Ogre::Exception(Ogre::Exception::ERR_INVALID_STATE,
			  ERR_NBLINEMAP, _filename);
  addCharacter(Ogre::Vector2(100, 100));
  addCharacter(Ogre::Vector2(900, 900));

  addBomb(Ogre::Vector2(900, 900));
  generatePlan();
}

void 		MapManager::generateSpawn()
{
  _spawns.push_front(Ogre::Vector2(MapManager::boxWidth, MapManager::boxWidth));
  _spawns.push_front(Ogre::Vector2(MapManager::boxWidth,
				   (_size * MapManager::boxWidth) -
				   (MapManager::boxWidth * 2)));
  _spawns.push_front(Ogre::Vector2(
	  (_size * MapManager::boxWidth) - (MapManager::boxWidth * 2),
	  MapManager::boxWidth));
  _spawns.push_front(Ogre::Vector2(
	  (_size * MapManager::boxWidth) - (MapManager::boxWidth * 2),
	  (_size * MapManager::boxWidth) - (MapManager::boxWidth * 2)));
}

void 		MapManager::addCharacter(const Ogre::Vector2 &vector)
{
  AGameObject	*player;

  player = new Player(AGameObject::CHARACTER);
  _character.push_back(player);
  player->setSceneManager(_SceneManager);
  player->createEntity();
  player->setPosition(vector.x, player->getPositionY(), vector.y);
  player->AttachObject();
}

void 		MapManager::addBomb(const Ogre::Vector2 &vector)
{
  addObjects(Ogre::Vector2(vector.x, vector.y), new Bomb(AGameObject::BOMB));
}

void 		MapManager::setSize(int size)
{
  _size = size;
}

int 		MapManager::getSize() const
{
  return _size;
}

const std::vector<AGameObject *> &MapManager::getCharacter() const
{
  return _character;
}

AGameObject			*MapManager::getObjectFrom(Ogre::Vector2 const &pos) const
{
  std::multimap<Ogre::Vector2, AGameObject *>::const_iterator it;

  it = _objects.find(Ogre::Vector2(pos.x - std::fmod(pos.x, 100), pos.y - std::fmod(pos.y, 100)));
  if (it != _objects.end())
    return (it->second);
  return (NULL);
}

AGameObject			*MapManager::getObjectFrom(Ogre::Vector3 const &pos) const
{
  std::multimap<Ogre::Vector2, AGameObject *>::const_iterator it;

  std::cout << "search " << pos << " in map" << std::endl;
  //it = _objects.find(Ogre::Vector2(pos.x - std::fmod(pos.x, 100), pos.y - std::fmod(pos.y, 100)));
  it = _objects.find(Ogre::Vector2(100, 100));
  if (it != _objects.end())
    return (it->second);
  return (NULL);
}