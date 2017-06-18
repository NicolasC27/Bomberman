//
// Created by nicolas on 12/06/17.
//

#ifndef BOMBERMAN_EXPLOSION_HPP
#define BOMBERMAN_EXPLOSION_HPP


class AGameObject;

#include "Interfaces/AGameObject.hpp"

class Explosion : public AGameObject
{
 public:
  Explosion(MapManager *map, AGameObject::Object object, int isRoot, int Lenght, Ogre::Vector3 direction);

  virtual ~Explosion();

  void			createEntity();

  std::string 		getName() const;
  AGameObject::State 	getState() const;
  std::string		getMaterialName() const;
  Ogre::Vector3 	getScale() const;
  double		getPositionY() const;

  void 			update(Ogre::Real);

  Ogre::SceneManager::PrefabType	getMeshPrefab() const;
  std::string				getMeshName() const;
  std::string 				getNameExplosion() const;

  void 					extendFire(Ogre::Vector3 const &);
  bool 					checkVictim(Ogre::Vector3 const &, Ogre::Vector3 const &);

 private:

  std::string		_name;

  Ogre::Real 		delayExtend;
  Ogre::Real		lifeTimeRemaning;
  Ogre::Vector3 	_Direction;
  Ogre::Real		_deleteDelay;

  bool 			_extend;
  bool 			_delete;
  int 			_IsRoot;
  int 			_Length;

};

#endif //BOMBERMAN_EXPLOSION_HPP
