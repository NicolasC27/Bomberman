//
// Created by nicolas on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_MAP_HPP
#define CPP_INDIE_STUDIO_MAP_HPP

#include <OgreVector2.h>
#include <OgreException.h>
#include <map>
#include "AGameObject.hpp"

#define ERR_MAPSIZE	"Size map too big"
#define ERR_NBLINEMAP	"The number of rows does not match the number of rows in the map."
#define NOT_FOUND	"File not found"
#define FOLDER_MAP	"media/map/"

class Map
{

 public:
  Map(std::string const &filename = "Media/map/map1");
  virtual ~Map();


 private:
  std::multimap<Ogre::Vector2, AGameObject *> 	_objects;
  std::multimap<AGameObject *, Ogre::Vector2> 	_character;
 public:
  void 	addCharacter(const Ogre::Vector2 &vector, AGameObject *character);

 private:
  std::list<Ogre::Vector2>			_spawns;
  std::string	 				_filename;
  int 						_size;

 public:
  void	generateObjects();
  void	generateSpawn();
  void	setSize(int size);
  void 	addObjects(const Ogre::Vector2 &, AGameObject *);

};

#endif //CPP_INDIE_STUDIO_MAP_HPP
