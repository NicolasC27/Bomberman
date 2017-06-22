//
// Created by nicolas on 29/05/17.
//

#ifndef BOMBERMAN_MAP_HPP
#define BOMBERMAN_MAP_HPP

class MapManager;

#include <OgreVector2.h>
#include <OgreException.h>
#include <map>
#include <algorithm>
#include <irrKlang/ik_ISoundEngine.h>
#include "Interfaces/AGameObject.hpp"
#include "Common/Manager/NodeManager.hpp"

#define ERR_MAPSIZE	"Size map too big"
#define ERR_NBLINEMAP	"The number of rows does not match the number of rows in the map."
#define NOT_FOUND	"File not found"
#define FOLDER_MAP	"media/map/"
#define CUBE_WIDTH	MapManager::boxWidth

class MapManager
{
 public:
  static const int 				boxWidth = 100;
  static const int 				halfboxWidth = 50;

 private:
  irrklang::ISoundEngine			* engine;

  NodeManager 					*_nodes;
  Ogre::SceneManager 				*_SceneManager;

public:
  typedef std::map<AGameObject *, Ogre::Vector2> 	Objects;

  typedef std::map<int, AGameObject *>			Delete;
  typedef std::vector<AGameObject *>			Character;

  Objects						_objects;
  Delete					 	_waitDelete;
  Character						_character;
  Character						_walls;

  AGameObject			   	*getWallFrom(Ogre::Vector2 const &) const;
  AGameObject			   	*getObjectFrom(Ogre::Vector2 const &) const;
  AGameObject				*getObjectFrom(Ogre::Vector3 const &) const;
  Ogre::Vector2				getPosFrom(Ogre::Vector2 const &) const;
  Ogre::Vector2				getPosFrom(Ogre::Vector3 const &) const;
  irrklang::ISoundEngine		*getEngine() const;

  Character						getCharacterFrom(Ogre::Vector2 const &) const;

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

  void 			update(Ogre::Real);

  void 			removeObject(AGameObject *object);
  void 			removeWall(AGameObject *object);
  void 			removeCharacter(AGameObject *object);

  void 			reset();

 protected:
  irrklang::ISoundSource			*general;
  irrklang::ISoundSource			*explosion;
  irrklang::ISoundSource			*pause;
  irrklang::ISoundSource			*winner;
  irrklang::ISoundSource			*confirm;
  irrklang::ISoundSource			*player_out;
  irrklang::ISoundSource			*getitem;
  irrklang::ISoundSource			*fall;
  irrklang::ISoundSource			*wallOnGround;

 public:
  irrklang::ISoundSource 			*getExplosion() const;
  irrklang::ISoundSource 			*getPause() const;
  irrklang::ISoundSource 			*getWinner() const;
  irrklang::ISoundSource 			*getConfirm() const;
  irrklang::ISoundSource 			*getPlayer_out() const;
  irrklang::ISoundSource 			*getGetitem() const;
  irrklang::ISoundSource 			*getFall() const;
  irrklang::ISoundSource 			*getWallOnGround() const;

  void deleteWaitObject();

  AGameObject *getObjectFrom(int id) const;
};

#endif //BOMBERMAN_MAP_HPP
