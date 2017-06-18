//
// Created by nicolas on 12/06/17.
//

#ifndef BOMBERMAN_ITEM_HPP
#define BOMBERMAN_ITEM_HPP

#include <OgreVector3.h>
#include "Interfaces/AGameObject.hpp"

#define	NB_UPGRADE	7

std::vector<std::string> mesh_item = {"Sphere.mesh",
				      "Sphere.mesh",
				      "Sphere.mesh",
				      "Sphere.mesh",
				      "Sphere.mesh",
				      "Sphere.mesh",
				      "Sphere.mesh"};
			     
void    (*use_item)[7]() = {Player::powerup,
			    Player::rangeup,
			    Player::speedup,
			    Player::throwing,
			    Player::pushing,
			    Player::godmode,
			    Player::ghostmode};

class Item : public AGameObject
{
  std::string		_name;
  int			upgrade;
  
 public:
  Item(Object object);

  virtual ~Item();

  void			createEntity();

  std::string 		getName() const;
  State 		getState() const;
  std::string		getMaterialName() const;
  Ogre::Vector3 	getScale() const;
  double		getPositionY() const;

  Ogre::SceneManager::PrefabType	getMeshPrefab() const;
  std::string				getMeshName() const;

};

#endif //BOMBERMAN_BOMB_HPP
