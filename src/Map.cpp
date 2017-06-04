//
// Created by nicolas on 29/05/17.
//

#include "Map.hpp"
#include "Wall.hpp"


Map::Map(std::string const &filename, Ogre::SceneManager *SceneManager,
	 Controller::NodeManager *node) : _filename(filename), _SceneManager(SceneManager), _nodes(node)
{
  std::ifstream infile(filename);

  if (!(infile.good()))
    throw Ogre::Exception(Ogre::Exception::ERR_FILE_NOT_FOUND,
			  NOT_FOUND, FOLDER_MAP);
}

Map::~Map()
{

}

void 		Map::addObjects(const Ogre::Vector2 &vector, AGameObject *object)
{
  _objects.insert(std::pair<Ogre::Vector2, AGameObject *>(vector, object));
  object->setSceneManager(_SceneManager);
  object->createEntity();
  object->setPosition(Map::boxWidth * (vector.x), 0, Map::boxWidth * vector.y);
  object->AttachObject();

}

void 		Map::generateObjects()
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
      double xPos = Map::boxWidth * x;
      for(int z = 0, i = 0; line[i]; i++, z++)
	{
	  double zPos = Map::boxWidth * z;
	  if ((line[i] - '0') == AGameObject::WALL)
	    addObjects(Ogre::Vector2(z, x), new Wall(Wall::UNBREAKABLE));
	  else if ((line[i] - '0')  == AGameObject::BLOCK)
	      addObjects(Ogre::Vector2(z, x), new Wall(Wall::BREAKABLE)); }
      count = x;
  }
//  if (count != (_size - 1))
//    throw Ogre::Exception(Ogre::Exception::ERR_INVALID_STATE,
//			  ERR_NBLINEMAP, _filename);


}

void 		Map::generateSpawn()
{
  _spawns.push_front(Ogre::Vector2(0, 0));
  _spawns.push_front(Ogre::Vector2(0, _size - 1));
  _spawns.push_front(Ogre::Vector2(_size - 1, 0));
  _spawns.push_front(Ogre::Vector2(_size - 1, _size - 1));
}

void 		Map::addCharacter(const Ogre::Vector2 &vector, AGameObject *character)
{
  _character.insert(std::pair<AGameObject *, Ogre::Vector2>(character, vector));
}

void 		Map::setSize(int size)
{
  _size = size;
}
