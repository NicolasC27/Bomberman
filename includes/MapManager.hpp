//
// Created by nicolas on 29/05/17.
//

#ifndef BOMBERMAN_MAP_HPP
#define BOMBERMAN_MAP_HPP

class MapManager;

#include <OgreVector2.h>
#include <OgreException.h>
#include <map>
#include "Interfaces/AGameObject.hpp"
#include "Common/Manager/NodeManager.hpp"

#define ERR_MAPSIZE	"Size map too big"
#define ERR_NBLINEMAP	"The number of rows does not match the number of rows in the map."
#define NOT_FOUND	"File not found"
#define FOLDER_MAP	"media/map/"
#define CUBE_WIDTH	MapManager::boxWidth
#define MAX_MAP		(map->getSize() * CUBE_WIDTH)

class MapManager
{
 public:
  static const int 				boxWidth = 100;
  static const int 				halfboxWidth = 50;

 public:
  NodeManager 					*_nodes;
  Ogre::SceneManager 				*_SceneManager;

  typedef std::map<AGameObject *, Ogre::Vector2> 	Objects;
  Objects						_objects;

  typedef std::vector<AGameObject *>			Character;
  Character						_character;

public:
  AGameObject			   *getObjectFrom(Ogre::Vector2 const &) const;
  AGameObject			   *getObjectFrom(Ogre::Vector3 const &) const;

private:
  std::list<Ogre::Vector2> 			_spawns;
  std::string 					_filename;

  int 						_size;
  int 						_isdestructible;

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

  bool 			getObject(Ogre::Vector2 vector);
  const 		Objects &getObjects() const;
  Ogre::Vector2		&getPosFrom(Ogre::Vector2 &tmp) const;

  Ogre::Vector2	const	getMiddlePosFrom(Ogre::Vector2 const &tmp) const;
  int			getIsdestructible() const;

  void 			setIsdestructible(int isdestructible);

  void 			remove(AGameObject *object);
  void 			removeObject(AGameObject *object);
};

#endif //BOMBERMAN_MAP_HPP
