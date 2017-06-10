//
// Created by nicolas on 29/05/17.
//

#include "Objects/Wall.hpp"
#include "Objects/Player.hpp"
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
//	  else
//	      addObjects(Ogre::Vector2(z, x), new Ground(Ground::UNBREAKABLE));
	}
      count = x;
  }
  if (count != (_size - 1))
    throw Ogre::Exception(Ogre::Exception::ERR_INVALID_STATE,
			  ERR_NBLINEMAP, _filename);
  addCharacter(Ogre::Vector2(500, 500));
  generatePlan();
}

void 		MapManager::generateSpawn()
{
  _spawns.push_front(Ogre::Vector2(MapManager::boxWidth, MapManager::boxWidth));
  _spawns.push_front(Ogre::Vector2(MapManager::boxWidth, (_size * 1000) - MapManager::boxWidth));
  _spawns.push_front(Ogre::Vector2((_size * 1000) - MapManager::boxWidth, MapManager::boxWidth));
  _spawns.push_front(Ogre::Vector2((_size * 1000) - MapManager::boxWidth, (_size * 1000) - MapManager::boxWidth));
}

void 		MapManager::addCharacter(const Ogre::Vector2 &vector)
{
  ACharacter	*player;

  player = new Player(AGameObject::CHARACTER);
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

void MapManager::move(const Ogre::Vector3 &vector3, const Ogre::FrameEvent &evt)
{
  _character.front()->move(vector3, evt);
}