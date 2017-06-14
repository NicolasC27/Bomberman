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
 public:
  static const int 				boxWidth = 100;

 private:
  NodeManager 					*_nodes;
  Ogre::SceneManager 				*_SceneManager;

  typedef std::map<AGameObject *, Ogre::Vector2>	Objects;
  Objects	_objects;

 private:

  std::vector<AGameObject *>			_character;
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

  void					setSize(int size);

  int					getSize() const;
  const std::vector<AGameObject *> &	getCharacter() const;

  void 			addObjects(const Ogre::Vector2 &, AGameObject *);
  void 			addCharacter(const Ogre::Vector2 &vector);
  void 			addBomb(const Ogre::Vector2 &vector);

  void 			update(Ogre::Real);

  bool getObject(const Ogre::Vector2 &vector);
};

#endif //CPP_INDIE_STUDIO_MAP_HPP
