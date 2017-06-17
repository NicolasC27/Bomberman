//
// Created by nicolas on 12/06/17.
//

#ifndef BOMBERMAN_BOMB_HPP
#define BOMBERMAN_BOMB_HPP

class Bomb;

#include <OgreVector3.h>
#include "Interfaces/AGameObject.hpp"
#include "Objects/Player.hpp"

class Bomb : public AGameObject
{
  Player		*_player;
  std::string		_name;
  float			explosionDelay;
  int 			_power;

 public:
  Bomb(Player *player, MapManager *map, Object object);

  virtual ~Bomb();

  void			createEntity();

  std::string 		getName() const;
  State 		getState() const;
  std::string		getMaterialName() const;
  Ogre::Vector3 	getScale() const;
  double		getPositionY() const;

  void 			update(Ogre::Real);

  Ogre::SceneManager::PrefabType	getMeshPrefab() const;
  std::string				getMeshName() const;

  std::string getNameExplosion() const;

  void 			explode();
  virtual void		destroy();
};

#endif //BOMBERMAN_BOMB_HPP
