//
// Created by nicolas on 12/06/17.
//

#ifndef BOMBERMAN_ITEM_HPP
#define BOMBERMAN_ITEM_HPP

#include <OgreParticleSystem.h>
#include <OgreParticleSystemManager.h>
#include <OgreVector2.h>
#include <OgreVector3.h>
#include "Interfaces/AGameObject.hpp"
#include "Objects/Player.hpp"

#define	NB_UPGRADE	7

class Item : public AGameObject
{
  int			upgrade;
  int 			_bombType;

 public:
  Item(MapManager *, Object object);

  virtual ~Item();

  void 			update(Ogre::Real);
  virtual void		destroy();

  void			createEntity();

  int 			getUpgrade() const;
  std::string 		getName() const;
  State 		getState() const;
  std::string		getMaterialName() const;
  Ogre::Vector3 	getScale() const;
  double		getPositionY() const;

  Ogre::SceneManager::PrefabType	getMeshPrefab() const;
  std::string				getMeshName() const;

};

#endif //BOMBERMAN_BOMB_HPP
