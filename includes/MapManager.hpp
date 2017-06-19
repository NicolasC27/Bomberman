//
// Created by nicolas on 29/05/17.
//

#ifndef BOMBERMAN_MAP_HPP
#define BOMBERMAN_MAP_HPP

class MapManager;

#include <OgreVector2.h>
#include <OgreException.h>
#include <map>
#include <irrKlang/ik_ISoundEngine.h>
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
  irrklang::ISoundEngine			* engine;

  irrklang::ISoundEngine 			*getEngine() const;

  NodeManager 					*_nodes;
  Ogre::SceneManager 				*_SceneManager;

  typedef std::map<AGameObject *, Ogre::Vector2> 	Objects;
  Objects						_objects;

  typedef std::map<int, AGameObject *>			Delete;
  Delete					 	_waitDelete;

  typedef std::vector<AGameObject *>			Character;
  Character						_character;

  Character						_walls;
public:
  AGameObject			   	*getWallFrom(Ogre::Vector2 const &) const;
  AGameObject			   	*getObjectFrom(Ogre::Vector2 const &) const;
  AGameObject				*getObjectFrom(Ogre::Vector3 const &) const;
  Ogre::Vector2				getPosFrom(Ogre::Vector2 const &) const;
  Ogre::Vector2				getPosFrom(Ogre::Vector3 const &) const;
  Ogre::Vector2				getMiddlePosFrom(Ogre::Vector2 const &) const;
  Character				getCharacterFrom(Ogre::Vector2 const &) const;

private:
  std::vector<Ogre::Vector2> 			_spawns;
  std::string 					_filename;

  int 						_size;
  int 						_isdestructible;

 public:

  MapManager(std::string const &filename = "media/map/map1",
      Ogre::SceneManager *SceneManager = NULL,
      NodeManager *node = NULL);

  virtual ~MapManager();

  void			generateObjects(bool);
  void			generateSpawn();
  void			generatePlan();

  void			setSize(int size);
  void 			setSound();

  int			getSize() const;
  const Character &	getCharacter() const;

  void 			addObjects(const Ogre::Vector2 &, AGameObject *);
  void 			addWall(const Ogre::Vector2 &, AGameObject *);
  void 			addCharacter(const Ogre::Vector2 &vector, int id = 0);
  void 			addBomb(const Ogre::Vector2 &vector);

  void 			update(Ogre::Real);

  bool 			getObject(Ogre::Vector2 vector);
  const 		Objects &getObjects() const;

  int			getIsdestructible() const;

  void 			setIsdestructible(int isdestructible);

  void 			remove(AGameObject *object);
  void 			removeObject(AGameObject *object);
  void 			removeWall(AGameObject *object);
  void 			removeCharacter(AGameObject *object);

  void 			reset();

 protected:
  irrklang::ISoundSource			*general;
  irrklang::ISoundSource			*explosion;
 /* irrklang::ISoundSource			*pause;
  irrklang::ISoundSource			*winner;
  irrklang::ISoundSource			*confirm;
  irrklang::ISoundSource			*player_out;
  irrklang::ISoundSource			*getitem;
  irrklang::ISoundSource			*fall;
  irrklang::ISoundSource			*wallOnGround;*/

 public:
  irrklang::ISoundSource 			*getExplosion() const;

  void deleteWaitObject();

  AGameObject *getObjectFrom(int id) const;
};

#endif //BOMBERMAN_MAP_HPP
