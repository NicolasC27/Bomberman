//
// Created by nicolas on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_MAP_HPP
#define CPP_INDIE_STUDIO_MAP_HPP

#include <OgreVector2.h>
#include <OgreException.h>
#include <map>
#include "Controller/GameManager.hpp"
#include "Controller/NodeManager.hpp"
#include "AGameObject.hpp"

#define ERR_MAPSIZE	"Size map too big"
#define ERR_NBLINEMAP	"The number of rows does not match the number of rows in the map."
#define NOT_FOUND	"File not found"
#define FOLDER_MAP	"media/map/"

class Map
{
 private:
  static const int				boxWidth = 100;

  Controller::NodeManager			*_nodes;
  Ogre::SceneManager				*_SceneManager;

  std::multimap<Ogre::Vector2, AGameObject *> 	_objects;
  std::multimap<AGameObject *, Ogre::Vector2> 	_character;
  std::list<Ogre::Vector2>			_spawns;
  std::string	 				_filename;
  int 						_size;

 public:

  Map(std::string const &filename = "media/map/map1", Ogre::SceneManager *SceneManager = NULL, Controller::NodeManager *node = NULL);
  virtual ~Map();

  void	generateObjects();
  void	generateSpawn();

  void	setSize(int size);

  void 	addObjects(const Ogre::Vector2 &, AGameObject *);
  void 	addCharacter(const Ogre::Vector2 &vector, AGameObject *character);
};

#endif //CPP_INDIE_STUDIO_MAP_HPP
