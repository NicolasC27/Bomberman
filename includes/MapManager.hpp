//
// Created by nicolas on 29/05/17.
//

#ifndef CPP_INDIE_STUDIO_MAP_HPP
#define CPP_INDIE_STUDIO_MAP_HPP

class MapManager;
#include <OgreVector2.h>
#include <OgreException.h>
#include <map>
#include "Common/Manager/NodeManager.hpp"
#include "Interfaces/AGameObject.hpp"

#define ERR_MAPSIZE	"Size map too big"
#define ERR_NBLINEMAP	"The number of rows does not match the number of rows in the map."
#define NOT_FOUND	"File not found"
#define FOLDER_MAP	"media/map/"

class MapManager
{
 private:
  static const int 				boxWidth = 100;

  NodeManager 					*_nodes;
  Ogre::SceneManager 				*_SceneManager;

  std::multimap<Ogre::Vector2, AGameObject *> 	_objects;
  std::vector<AGameObject *>			_character;
 public:
  const std::vector<AGameObject *> &getCharacter() const;

 private:

  std::list<Ogre::Vector2> 			_spawns;
  std::string 					_filename;

  int 						_size;

 public:

  MapManager(std::string const &filename = "media/map/map1",
      Ogre::SceneManager *SceneManager = NULL,
      NodeManager *node = NULL);

  virtual ~MapManager();

  void			generateObjects();
  void			generateSpawn();
  void			generatePlan();

  void			setSize(int size);
  int			getSize() const;

  void 			addObjects(const Ogre::Vector2 &, AGameObject *);
  void 			addCharacter(const Ogre::Vector2 &vector);
  void 			addBomb(const Ogre::Vector2 &vector);
};

#endif //CPP_INDIE_STUDIO_MAP_HPP
